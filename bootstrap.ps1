#Requires -Version 2

$baseDir = "$pwd\.build-deps"
$tmpDir = "$baseDir\tmp"
$binDir = "$baseDir\bin"

$env:Path = "$binDir;$env:Path"

$cmakeVersion = "3.1.0"
$cmakeBin = "$binDir\cmake.exe"
$cmakeInstall = "$pwd\scripts\install-cmake.ps1"

$perlVersion = "5.27.8"
$perlBin = "$binDir\perl.exe"
$perlInstall = "$pwd\scripts\install-perl5.ps1"

$curlVersion = "7.60.0"
$curlBin = "$binDir\curl.exe"
$curlInstall = "$pwd\scripts\install-curl.ps1"

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
