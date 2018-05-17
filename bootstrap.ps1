#Requires -Version 2

$cmakeVersion = "2.8.0"
$cmakeBaseDir = "$pwd\.cmake"
$cmake = "$cmakeBaseDir\bin\cmake.exe"
$installCmake = "$pwd\scripts\install-cmake.ps1"

if(!(Test-Path $cmakeBaseDir)) {
    New-Item -Type Directory $cmakeBaseDir | Out-Null
}

if (!(Get-Command $cmake  -errorAction SilentlyContinue))
{
    & $installCmake -Version $cmakeVersion -InstallPath $cmakeBaseDir
}
