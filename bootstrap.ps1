#Requires -Version 2

$baseDir = "$pwd\.build-deps"
$tmpDir = "$baseDir\tmp"

$cmakeVersion = "3.1.0"
$cmakeBin = "$baseDir\bin\cmake.exe"
$installCmake = "$pwd\scripts\install-cmake.ps1"

if(!(Test-Path $tmpDir)) {
    New-Item -Type Directory $tmpDir | Out-Null
}

if (!(Test-Path $cmakeBin))
{
    & $installCmake -Version $cmakeVersion -InstallPath $baseDir -DownloadPath $tmpDir
}
