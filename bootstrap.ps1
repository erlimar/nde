#Requires -Version 3

$baseDir = "$PSScriptRoot\.build-deps"
$tmpDir = "$baseDir\tmp"
$binDir = "$baseDir\bin"

$env:Path = "$binDir;$env:Path"

$cmakeVersion = "3.1.0"
$cmakeBin = "$binDir\cmake.exe"
$cmakeInstall = "$PSScriptRoot\scripts\install-cmake.ps1"

$perlVersion = "5.27.8"
$perlBin = "$binDir\perl.exe"
$perlInstall = "$PSScriptRoot\scripts\install-perl5.ps1"

$curlVersion = "7.60.0"
$curlBin = "$binDir\curl.exe"
$curlInstall = "$PSScriptRoot\scripts\install-curl.ps1"

if(!(Test-Path $tmpDir)) {
    New-Item -Type Directory $tmpDir | Out-Null
}

if (!(Test-Path $cmakeBin))
{
    & $cmakeInstall -Version $cmakeVersion -InstallPath $baseDir -DownloadPath $tmpDir
}

if (!(Test-Path $perlBin))
{
    & $perlInstall -Version $perlVersion -InstallPath $baseDir -DownloadPath $tmpDir
}

if (!(Test-Path $curlBin))
{
    & $curlInstall -Version $curlVersion -InstallPath $baseDir -DownloadPath $tmpDir -BuildStatic -BuildExe
}
