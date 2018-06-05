#Requires -Version 3

param (
	[string] $Version = $(throw "-Version is required."),
	[string] $InstallPath = $(throw "-InstallPath is required."),
    [string] $DownloadPath = "",
    [switch] $BuildStatic = $false,
    [switch] $UseZLib = $false,
    [switch] $UseZLibStatic = $false,
    [string] $ZLibSystemPath = "",
    [string] $ZLibIncludePath = "",
    [string] $ZLibLibPath = ""
)

if($InstallPath.StartsWith("./")) { $InstallPath = $InstallPath.replace("./", "$pwd/") }
if($InstallPath.StartsWith(".\")) { $InstallPath = $InstallPath.replace(".\", "$pwd\") }

if("${DownloadPath}" -eq "") {
    $DownloadPath = $InstallPath
} else {
    if($DownloadPath.StartsWith("./")) { $DownloadPath = $DownloadPath.replace("./", "$pwd/") }
    if($DownloadPath.StartsWith(".\")) { $DownloadPath = $DownloadPath.replace(".\", "$pwd\") }
}

$InstallPath = [System.IO.Path]::GetFullPath($InstallPath)
$DownloadPath = [System.IO.Path]::GetFullPath($DownloadPath)

$X86ProcessorArch = "x86"
$X86WindowsArch = "win32"
$X64ProcessorArch = "x64"
$X64WindowsArch = "win64"

$processorArch = $X86ProcessorArch
$windowsArch = $X86WindowsArch

if([IntPtr]::Size -eq 8) {
	$processorArch = $X64ProcessorArch
	$windowsArch = $X64WindowsArch
}

if(($UseZLib -eq $false) -and ($UseZLibStatic -eq $false)) {
    $ZLibSystemPath = ""
    $ZLibIncludePath = ""
    $ZLibLibPath = ""
} elseif ($UseZLibStatic -eq $true) {
    if("$ZLibSystemPath" -eq "") {
        $ZLibSystemPath = $InstallPath
    }
    $ZLibIncludePath = ($ZLibIncludePath, [System.IO.Path]::Combine($ZLibSystemPath, "include"))["$ZLibIncludePath" -eq ""]
    $ZLibLibPath = ($ZLibLibPath, [System.IO.Path]::Combine($ZLibSystemPath, "lib", "zlib.lib"))["$ZLibLibPath" -eq ""]
} else {
    if("$ZLibSystemPath" -eq "") {
        $ZLibSystemPath = $InstallPath
    }
    $ZLibIncludePath = ($ZLibIncludePath, [System.IO.Path]::Combine($ZLibSystemPath, "include"))["$ZLibIncludePath" -eq ""]
    $ZLibLibPath = ($ZLibLibPath, [System.IO.Path]::Combine($ZLibSystemPath, "lib", "zdll.lib"))["$ZLibLibPath" -eq ""]
}

Add-Type -AssemblyName System.IO.Compression.FileSystem

function Extract-ZipFile
{
    param
	(
		[string]$FilePath,
		[string]$DirPath
	)

    [System.IO.Compression.ZipFile]::ExtractToDirectory($FilePath, $DirPath)
}

function Get-WebFile
{
    param (
        [string] $Url,
        [string] $Path
    )
    
    $wc = New-Object System.Net.WebClient
	
	# Credencials
	$wc.UseDefaultCredentials = $true
	
	# Proxy
	$wc.Proxy = [System.Net.WebRequest]::DefaultWebProxy
	$wc.Proxy.Credentials = [System.Net.CredentialCache]::DefaultNetworkCredentials

    $wc.DownloadFile($Url, $Path)
}

function Get-OpenSSLSourceFileUrl
{
	for($i = 0; $i -lt $versionFiles.Count; $i++) {
		if($versionFiles[$i] -eq $Version) {
            $nameSuffix = "OpenSSL_";
            $nameSuffix += $Version.replace('.','_');
		 	$fileName = "openssl-$nameSuffix.zip";
		 	$url = $urlTemplate.replace("{0}", $nameSuffix)
		 	break
		}
    }
    
	if($url -ne $urlTemplate){
		return @($fileName, $url)
	}
	
    return @()
}

# https://github.com/openssl/openssl/archive/{0}
$urlTemplate = "https://codeload.github.com/openssl/openssl/zip/{0}"

$versionFiles = @(
	"1.1.0", "1.1.0a", "1.1.0b", "1.1.0c", "1.1.0d", "1.1.0e", "1.1.0f", "1.1.0g", "1.1.0h"
)

if(!(Test-Path $InstallPath)) {
	New-Item -Type Directory $InstallPath | Out-Null
}

$OpenSSLZip = Get-OpenSSLSourceFileUrl

if($OpenSSLZip.Count -eq 0) {
	throw "OpenSSL v$Version not found!"
}

$OpenSSLLogFilePath = "$pwd\openssl-build.log"
$OpenSSLUrl = $OpenSSLZip[1]
$OpenSSLFileName = $OpenSSLZip[0]
$OpenSSLDirName = [System.IO.path]::GetFileNameWithoutExtension($OpenSSLFileName).replace("v", "openssl")
$OpenSSLFilePath = [System.IO.Path]::Combine($DownloadPath, $OpenSSLFileName)
$OpenSSLDirPath = [System.IO.Path]::Combine($DownloadPath, $OpenSSLDirName)
$OpenSSLBinFolderPath = [System.IO.Path]::Combine($InstallPath, "bin")
$OpenSSLBinPath = [System.IO.Path]::Combine($OpenSSLBinFolderPath, "openssl.exe")
$OpenSSLDirSSL = [System.IO.Path]::Combine($InstallPath, "share", "ssl")

"OpenSSLLogFilePath: $OpenSSLLogFilePath" | Write-Host
"OpenSSLUrl: $OpenSSLUrl" | Write-Host
"OpenSSLFileName: $OpenSSLFileName" | Write-Host
"OpenSSLDirName: $OpenSSLDirName" | Write-Host
"OpenSSLFilePath: $OpenSSLFilePath" | Write-Host
"OpenSSLDirPath: $OpenSSLDirPath" | Write-Host
"OpenSSLBinFolderPath: $OpenSSLBinFolderPath" | Write-Host
"OpenSSLBinPath: $OpenSSLBinPath" | Write-Host
"UseZLib: $UseZLib" | Write-Host
"UseZLibStatic: $UseZLibStatic" | Write-Host
"ZLibSystemPath: $ZLibSystemPath" | Write-Host
"ZLibIncludePath: $ZLibIncludePath" | Write-Host
"ZLibLibPath: $ZLibLibPath" | Write-Host

"Installing OpenSSL v$Version..." | Write-Host
"-----------------------------" | Write-Host

if(!(Test-Path $OpenSSLFilePath)) {
	" -> Downloading $OpenSSLUrl..." | Write-Host
	Get-WebFile -Url $OpenSSLUrl -Path $OpenSSLFilePath
}

if(!(Test-Path $OpenSSLDirPath)) {
    " -> Extracting $OpenSSLFileName" | Write-Host
	Extract-ZipFile -FilePath $OpenSSLFilePath -DirPath $DownloadPath
}

" -> Building source (this may take a while)..." | Write-Host
Push-Location $OpenSSLDirPath
#& nmake install INST_TOP=$InstallPath CCTYPE=$CCTYPE *> $OpenSSLLogFilePath
$paramTarget = "VC-WIN32"
$paramZLib = ""
$paramZLibInclude = ""
$paramZLibLib = ""
$paramStatic = ""

if( $BuildStatic -eq $true) {
    $paramStatic = "no-shared"
}

if( "$processorArch" -eq "x64" ) {
    $paramTarget = ("VC-WIN64I", "VC-WIN64A")["${env:PROCESSOR_ARCHITECTURE}" -eq "AMD64"]
}

if($UseZLibStatic -eq $true) {
    $paramZLib = "zlib"
    $paramZLibInclude = "--with-zlib-include=`"$ZLibIncludePath`""
    $paramZLibLib = "--with-zlib-lib=`"$ZLibLibPath`""
}
elseif ($UseZLib -eq $true) {
    $paramZLib = "zlib-dynamic"
    $paramZLibInclude = "--with-zlib-include=`"$ZLibIncludePath`""
    $paramZLibLib = "--with-zlib-lib=`"$ZLibLibPath`""
}else{
    $paramZLib = "no-comp"
}

perl Configure $paramTarget `
    --prefix="$InstallPath" `
    --openssldir="$OpenSSLDirSSL" `
    --release `
    $paramZLibInclude `
    $paramZLibLib `
    $paramZLib `
    $paramStatic `
    no-asm #*> $OpenSSLLogFilePath
    #threads
    #zlib-dynamic
    #no-static-engine
    #no-engine
    #no-threads
    
if(!($LastExitCode)) {
    nmake install #*>> $OpenSSLLogFilePath
}    
Pop-Location
    
if(!($LastExitCode)) {
    " -> Removing temporary files..." | Write-Host
	Remove-Item $OpenSSLDirPath -Force -Recurse
	Remove-Item $OpenSSLFilePath -Force
}

exit 1

if(!(Test-Path $OpenSSLBinPath)) {
	throw "OpenSSL v$Version install fail!"
}

"-----------------------------" | Write-Host
"OpenSSL v$Version successfully install!" | Write-Host
"" | Write-Host
