#Requires -Version 2

$cmakeVersion = "3.1.0"
$cmakeBaseDir = "$pwd\.cmake"
$cmake = "$cmakeBaseDir\bin\cmake.exe"
$installCmake = "$pwd\scripts\install-cmake.ps1"

if(!(Test-Path $cmakeBaseDir)) {
    New-Item -Type Directory $cmakeBaseDir | Out-Null
}

if (!(Test-Path $cmake))
{
    & $installCmake -Version $cmakeVersion -InstallPath $cmakeBaseDir
}
