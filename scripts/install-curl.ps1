#Requires -Version 3

param (
	[string] $Version = $(throw "-Version is required."),
	[string] $InstallPath = $(throw "-InstallPath is required."),
    [string] $DownloadPath = "",
    [switch] $UseOpenSSL = $false,
    [switch] $UseZLibStatic = $false,
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

# Detect VC version
if ("$env:VS150COMNTOOLS" -ne "") {
    $VC = "15"
}
elseif ("$env:VS140COMNTOOLS" -ne "") {
     $VC = "14"
}
elseif ("$env:VS120COMNTOOLS" -ne "") {
    $VC = "12"
}
elseif ("$env:VS110COMNTOOLS" -ne "") {
    $VC = "11"
}
elseif ("$env:VS100COMNTOOLS" -ne "") {
    $VC = "10"
}
elseif ("$env:VS90COMNTOOLS" -ne "") {
    $VC = "9"
}
elseif ("$env:VS80COMNTOOLS" -ne "") {
    $VC = "8"
}
else {
    $VC = "6"
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

function Get-CURLLSourceFileUrl
{
	$fileNameOriginal = "curl-${Version}.zip"
	$url = $urlTemplate
	
	for($i = 0; $i -lt $versionFiles.Count; $i++) {
		if($versionFiles[$i] -eq $fileNameOriginal) {
		 	$fileName = $fileNameOriginal
		 	$url = $url.replace("{0}", $versionFiles[$i])
		 	break
		}
	}
	
	if($url -ne $urlTemplate){
		return @($fileName, $url)
	}
	
    return @()
}

# mirror: Canada (Vancouver)                -> https://curl.mirror.anstey.ca/{0}
# mirror: Canada (Fastly (worldwide))       -> https://curl.haxx.se/download/{0}
# mirror: Germany (St. Wendel, Saarland)    -> https://dl.uxnr.de/mirror/curl/{0}
# mirror: Singapore                         -> https://execve.net/mirror/curl/{0}
# mirror: US (Houston, Texas)               -> https://curl.askapache.com/{0}
$urlTemplate = "https://curl.askapache.com/{0}"

$versionFiles = @(
	"curl-7.20.0.zip", "curl-7.20.1.zip",
	"curl-7.21.0.zip", "curl-7.21.1.zip", "curl-7.21.2.zip", "curl-7.21.3.zip", "curl-7.21.4.zip", "curl-7.21.5.zip", "curl-7.21.6.zip", "curl-7.21.7.zip",
	"curl-7.22.0.zip",
	"curl-7.23.0.zip", "curl-7.23.1.zip",
	"curl-7.24.0.zip",
	"curl-7.25.0.zip",
	"curl-7.26.0.zip",
	"curl-7.27.0.zip",
	"curl-7.28.0.zip", "curl-7.28.1.zip",
	"curl-7.29.0.zip",
	"curl-7.30.0.zip",
	"curl-7.31.0.zip",
	"curl-7.32.0.zip",
	"curl-7.33.0.zip",
	"curl-7.34.0.zip",
	"curl-7.35.0.zip",
	"curl-7.36.0.zip",
	"curl-7.37.0.zip", "curl-7.37.1.zip",
	"curl-7.38.0.zip",
	"curl-7.39.0.zip",
	"curl-7.40.0.zip",
	"curl-7.41.0.zip",
	"curl-7.42.0.zip", "curl-7.42.1.zip",
	"curl-7.43.0.zip",
	"curl-7.44.0.zip",
	"curl-7.45.0.zip",
	"curl-7.46.0.zip",
	"curl-7.47.0.zip", "curl-7.47.1.zip",
	"curl-7.48.0.zip",
	"curl-7.49.0.zip", "curl-7.49.1.zip",
	"curl-7.50.0.zip", "curl-7.50.1.zip", "curl-7.50.2.zip", "curl-7.50.3.zip",
	"curl-7.51.0.zip",
	"curl-7.52.0.zip", "curl-7.52.1.zip",
	"curl-7.53.0.zip", "curl-7.53.1.zip",
	"curl-7.54.0.zip", "curl-7.54.1.zip",
	"curl-7.55.0.zip", "curl-7.55.1.zip",
	"curl-7.56.0.zip", "curl-7.56.1.zip",
	"curl-7.57.0.zip",
	"curl-7.58.0.zip",
	"curl-7.59.0.zip",
	"curl-7.60.0.zip"
)

if(!(Test-Path $InstallPath)) {
	New-Item -Type Directory $InstallPath | Out-Null
}

$curlZip = Get-CURLLSourceFileUrl

if($curlZip.Count -eq 0) {
	throw "CURL v$Version not found!"
}

$CURLLogFilePath = "$pwd\curl-build.log"
$CURLUrl = $curlZip[1]
$CURLFileName = $curlZip[0]
$CURLDirName = [System.IO.path]::GetFileNameWithoutExtension($CURLFileName)
$CURLFilePath = [System.IO.Path]::Combine($DownloadPath, $CURLFileName)
$CURLDirPath = [System.IO.Path]::Combine($DownloadPath, $CURLDirName)
$CURLBinFolderPath = [System.IO.Path]::Combine($InstallPath, "bin")
$CURLBinPath = [System.IO.Path]::Combine($CURLBinFolderPath, "curl.exe")
$CURLBuildPath = [System.IO.Path]::Combine($CURLDirPath, "winbuild")
$CURLDistPath = [System.IO.Path]::Combine($CURLDirPath, "builds")

"Installing CURL v$Version..." | Write-Host
"-----------------------------" | Write-Host

if(!(Test-Path $CURLFilePath)) {
	" -> Downloading $CURLUrl..." | Write-Host
	Get-WebFile -Url $CURLUrl -Path $CURLFilePath
}

if(!(Test-Path $CURLDirPath)) {
	" -> Extracting $CURLFileName" | Write-Host
	Extract-ZipFile -FilePath $CURLFilePath -DirPath $DownloadPath
}

" -> Building source (this may take a while)..." | Write-Host
if (!(Test-Path $CURLBuildPath)) {
    New-Item -Type Directory $CURLBuildPath | Out-Null
}

# TODO: Parameter
$WithDevel = $InstallPath

if($BuildStatic) {
    $paramMode = "static"
} else {
    $paramMode = "dll"
}

if($UseOpenSSL) {
    # TODO: static/dll
    $paramSSL = "WITH_SSL=static"
} else {
    $paramSSL = "ENABLE_WINSSL=yes"
}

# if($UseZLibStatic) {
#     # TODO: static/dll
#     $paramZLib = "WITH_ZLIB=static"
# } else {
#     $paramZLib = "WITH_ZLIB=dll"
# }

Push-Location $CURLBuildPath
nmake /f Makefile.vc `
    VC=$VC `
    MODE=$paramMode `
    WITH_DEVEL=$WithDevel `
    $paramSSL `
    WITH_ZLIB=static `
    MACHINE=$processorArch `
    DEBUG=no > $CURLLogFilePath

if(!($LastExitCode)) {
    Copy-Item -Path "$CURLDistPath\**\bin" -Destination $InstallPath -Include "*" -Recurse -Force
    Copy-Item -Path "$CURLDistPath\**\include" -Destination $InstallPath -Include "*" -Recurse -Force
    Copy-Item -Path "$CURLDistPath\**\lib" -Destination $InstallPath -Include "*" -Recurse -Force
}
Pop-Location

if(!($LastExitCode)) {
	" -> Removing temporary files..." | Write-Host
	Remove-Item $CURLDirPath -Force -Recurse
	Remove-Item $CURLFilePath -Force
}

if(!(Test-Path $CURLBinPath)) {
	throw "CURL v$Version install fail!"
}

"-----------------------------" | Write-Host
"CURL v$Version successfully install!" | Write-Host
"" | write-host
