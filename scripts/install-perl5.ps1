#Requires -Version 2

param (
	[string] $Version = $(throw "-Version is required."),
	[string] $InstallPath = $(throw "-InstallPath is required."),
    [string] $DownloadPath = ""
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

# Detect CCTYPE
if ("$env:VS150COMNTOOLS" -ne "") {
    $CCTYPE = "MSVC141"
}
elseif ("$env:VS140COMNTOOLS" -ne "") {
     $CCTYPE = "MSVC140"
}
elseif ("$env:VS120COMNTOOLS" -ne "") {
    $CCTYPE = "MSVC120"
}
elseif ("$env:VS110COMNTOOLS" -ne "") {
    $CCTYPE = "MSVC110"
}
elseif ("$env:VS100COMNTOOLS" -ne "") {
    $CCTYPE = "MSVC100"
}
elseif ("$env:VS90COMNTOOLS" -ne "") {
    $CCTYPE = "MSVC90"
}
elseif ("$env:VS80COMNTOOLS" -ne "") {
    $CCTYPE = "MSVC80"
}
else {
    $CCTYPE = "MSVC60"
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

function Get-PerlSourceFileUrl
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

# https://github.com/perl/perl5/archive/{0}
$urlTemplate = "https://codeload.github.com/Perl/perl5/zip/{0}"

$versionFiles = @(
	"v5.27.11",
	"v5.27.10",
	"v5.27.9",
	"v5.27.8",
	"v5.27.7",
	"v5.27.6",
	"v5.27.5",
	"v5.27.4",
	"v5.27.3",
	"v5.27.2",
	"v5.27.1",
	"v5.27.0",
	"v5.26.2",
	"v5.26.1",
	"v5.26.0",
	"v5.25.12",
	"v5.25.11",
	"v5.25.10",
	"v5.25.9",
	"v5.25.8",
	"v5.25.7",
	"v5.25.6",
	"v5.25.5",
	"v5.25.4",
	"v5.25.3",
	"v5.25.2",
	"v5.25.1",
	"v5.25.0",
	"v5.24.4",
	"v5.24.3",
	"v5.24.2",
	"v5.24.1",
	"v5.24.0",
	"v5.23.9",
	"v5.23.8",
	"v5.23.7",
	"v5.23.6",
	"v5.23.5",
	"v5.23.4",
	"v5.23.3",
	"v5.23.2",
	"v5.23.1",
	"v5.23.0",
	"v5.22.4",
	"v5.22.3",
	"v5.22.2",
	"v5.22.1",
	"v5.22.0",
	"v5.21.11",
	"v5.21.10",
	"v5.21.9",
	"v5.21.8",
	"v5.21.7",
	"v5.21.6",
	"v5.21.5",
	"v5.21.4",
	"v5.21.3",
	"v5.21.2",
	"v5.21.1",
	"v5.21.0",
	"v5.20.3",
	"v5.20.2",
	"v5.20.1",
	"v5.20.0",
	"v5.19.11",
	"v5.19.10",
	"v5.19.9",
	"v5.19.8",
	"v5.19.7",
	"v5.19.6",
	"v5.19.5",
	"v5.19.4",
	"v5.19.3",
	"v5.19.2",
	"v5.19.1",
	"v5.19.0",
	"v5.18.4",
	"v5.18.3",
	"v5.18.2",
	"v5.18.1",
	"v5.18.0",
	"v5.17.11",
	"v5.17.10",
	"v5.17.9",
	"v5.17.8",
	"v5.17.7.0",
	"v5.17.7",
	"v5.17.6",
	"v5.17.5",
	"v5.17.4",
	"v5.17.3",
	"v5.17.2",
	"v5.17.1",
	"v5.17.0",
	"v5.16.3",
	"v5.16.2",
	"v5.16.1",
	"v5.16.0",
	"v5.15.9",
	"v5.15.8",
	"v5.15.7",
	"v5.15.6",
	"v5.15.5",
	"v5.15.4",
	"v5.15.3",
	"v5.15.2",
	"v5.15.1",
	"v5.15.0",
	"v5.14.4",
	"v5.14.3",
	"v5.14.2",
	"v5.14.1",
	"v5.14.0",
	"v5.13.11",
	"v5.13.10",
	"v5.13.9",
	"v5.13.8",
	"v5.13.7",
	"v5.13.6",
	"v5.13.5",
	"v5.13.4",
	"v5.13.3",
	"v5.13.2",
	"v5.13.1",
	"v5.13.0",
	"v5.12.5",
	"v5.12.4",
	"v5.12.3",
	"v5.12.2",
	"v5.12.1",
	"v5.12.0",
	"v5.11.5",
	"v5.11.4",
	"v5.11.3",
	"v5.11.2",
	"v5.11.1",
	"v5.11.0",
	"v5.10.0"
)

if(!(Test-Path $InstallPath)) {
	New-Item -Type Directory $InstallPath | Out-Null
}

$perlZip = Get-PerlSourceFileUrl

if($perlZip.Count -eq 0) {
	throw "PERL v$Version not found!"
}

$PerlLogFilePath = "$pwd\perl-build.log"
$PerlUrl = $perlZip[1]
$PerlFileName = $perlZip[0]
$PerlDirName = [System.IO.path]::GetFileNameWithoutExtension($PerlFileName).replace("v5", "perl5-5")
$PerlFilePath = [System.IO.Path]::Combine($DownloadPath, $PerlFileName)
$PerlDirPath = [System.IO.Path]::Combine($DownloadPath, $PerlDirName)
$PerlBinFolderPath = [System.IO.Path]::Combine($InstallPath, "bin")
$PerlBinPath = [System.IO.Path]::Combine($PerlBinFolderPath, "perl.exe")
$PerlBuildPath = [System.IO.Path]::Combine($PerlDirPath, "win32")

"Installing PERL v$Version..." | Write-Host
"-----------------------------" | Write-Host

if(!(Test-Path $PerlFilePath)) {
	" -> Downloading $PerlUrl..." | Write-Host
	Get-WebFile -Url $PerlUrl -Path $PerlFilePath
}

if(!(Test-Path $PerlBuildPath)) {
	" -> Extracting $PerlFileName" | Write-Host
	Extract-ZipFile -FilePath $PerlFilePath -DirPath $DownloadPath
}

" -> Building source (this may take a while)..." | Write-Host
Push-Location $PerlBuildPath
& nmake install INST_TOP=$InstallPath CCTYPE=$CCTYPE > $PerlLogFilePath
Pop-Location

if(!($LastExitCode)) {
	" -> Removing temporary files..." | Write-Host
	Remove-Item $PerlDirPath -Force -Recurse
	Remove-Item $PerlFilePath -Force
}

if(!(Test-Path $PerlBinPath)) {
	throw "PERL v$Version install fail!"
}

"-----------------------------" | Write-Host
"PERL v$Version successfully install!" | Write-Host
"" | Write-host
