#Requires -Version 3

param (
	[string] $Version = $(throw "-Version is required."),
	[string] $InstallPath = $(throw "-InstallPath is required."),
    [string] $DownloadPath = "",
	[switch] $BuildStatic = $false
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

function Get-ZLibSourceFileUrl
{
	$fileNameOriginal = "v${Version}"
	$url = $urlTemplate
	
	for($i = 0; $i -lt $versionFiles.Count; $i++) {
		if($versionFiles[$i] -eq $fileNameOriginal) {
		 	$fileName = "$fileNameOriginal.zip"
		 	$url = $url.replace("{0}", $versionFiles[$i])
		 	break
		}
	}
	
	if($url -ne $urlTemplate){
		return @($fileName, $url)
	}
	
    return @()
}

# https://github.com/madler/zlib/archive/{0}
$urlTemplate = "https://codeload.github.com/madler/zlib/zip/{0}"

$versionFiles = @(
	"v1.2.0.5", "v1.2.0.6", "v1.2.0.7", "v1.2.0.8",
	"v1.2.1", "v1.2.1.1", "v1.2.1.2",
	"v1.2.2", "v1.2.2.1", "v1.2.2.2", "v1.2.2.3", "v1.2.2.4",
	"v1.2.3", "v1.2.3.1", "v1.2.3.2", "v1.2.3.3", "v1.2.3.4", "v1.2.3.5", "v1.2.3.6", "v1.2.3.7", "v1.2.3.8", "v1.2.3.9",
	"v1.2.4", "v1.2.4.1", "v1.2.4.2", "v1.2.4.3", "v1.2.4.4", "v1.2.4.5",
	"v1.2.5", "v1.2.5.1", "v1.2.5.2", "v1.2.5.3",
	"v1.2.6", "v1.2.6.1",
	"v1.2.7", "v1.2.7.1", "v1.2.7.2", "v1.2.7.3",
	"v1.2.8",
	"v1.2.9",
	"v1.2.10",
	"v1.2.11"
)

if(!(Test-Path $InstallPath)) {
	New-Item -Type Directory $InstallPath | Out-Null
}

$zLibZip = Get-ZLibSourceFileUrl

if($zLibZip.Count -eq 0) {
	throw "ZLib v$Version not found!"
}

$ZLibLogFilePath = "$pwd\zlib-build.log"
$ZLibUrl = $zLibZip[1]
$ZLibFileName = $zLibZip[0]
$ZLibDirName = [System.IO.path]::GetFileNameWithoutExtension($ZLibFileName).replace("v", "zlib-")
$ZLibFilePath = [System.IO.Path]::Combine($DownloadPath, $ZLibFileName)
$ZLibDirPath = [System.IO.Path]::Combine($DownloadPath, $ZLibDirName)
$ZLibBinFolderPath = [System.IO.Path]::Combine($InstallPath, "bin")
$ZLibIncludeFolderPath = [System.IO.Path]::Combine($InstallPath, "include")
$ZLibLibFolderPath = [System.IO.Path]::Combine($InstallPath, "lib")

if($BuildStatic) {
    $ZLibBinPath = [System.IO.Path]::Combine($ZLibLibFolderPath, "zlib.lib")
} else {
    $ZLibBinPath = [System.IO.Path]::Combine($ZLibLibFolderPath, "zdll.lib")
}

function Install-Headers
{
    if(!(Test-Path $ZLibIncludeFolderPath)) {
        New-Item -Type Directory $ZLibIncludeFolderPath | Out-Null
    }
    Copy-Item "$ZLibDirPath\zconf.h" -Destination $ZLibIncludeFolderPath | Out-Null
    Copy-Item "$ZLibDirPath\zlib.h" -Destination $ZLibIncludeFolderPath | Out-Null
    Copy-Item "$ZLibDirPath\zutil.h" -Destination $ZLibIncludeFolderPath | Out-Null
}

function Install-Shared
{
    Install-Static
    Copy-Item "$ZLibDirPath\*.dll" -Destination $ZLibBinFolderPath | Out-Null
}

function Install-Static
{
    Install-Headers
    Copy-Item "$ZLibDirPath\*.lib" -Destination $ZLibLibFolderPath | Out-Null
}

"Installing ZLib v$Version..." | Write-Host
"-----------------------------" | Write-Host

if(!(Test-Path $ZLibFilePath)) {
	" -> Downloading $ZLibUrl..." | Write-Host
	Get-WebFile -Url $ZLibUrl -Path $ZLibFilePath
}

if(!(Test-Path $ZLibDirPath)) {
	" -> Extracting $ZLibFileName" | Write-Host
	Extract-ZipFile -FilePath $ZLibFilePath -DirPath $DownloadPath
}

" -> Building source (this may take a while)..." | Write-Host
Push-Location $ZLibDirPath
if($BuildStatic) {
    & nmake -f win32/Makefile.msc zlib.lib *> $ZLibLogFilePath
}else{
    & nmake -f win32/Makefile.msc zdll.lib *> $ZLibLogFilePath
}
if(!($LastExitCode)) {
    " -> Moving install files..." | Write-Host
    if($BuildStatic) {
        Install-Static
    } else {
        Install-Shared
    }
}
Pop-Location

if(!($LastExitCode)) {
	" -> Removing temporary files..." | Write-Host
	Remove-Item $ZLibDirPath -Force -Recurse
	Remove-Item $ZLibFilePath -Force
}

if(!(Test-Path $ZLibBinPath)) {
	throw "ZLib v$Version install fail!"
}

"-----------------------------" | Write-Host
"ZLib v$Version successfully install!" | Write-Host
"" | Write-host
