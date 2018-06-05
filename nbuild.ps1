#Requires -Version 3

param([string] $command)

if ("$command" -eq "") {
    "Usage: nbuild command [arguments]" | Write-Host
    exit 1
}

for($count = 0; $count -lt $args.length; $count++) {
    $value = $args[$count]
    if("$value".contains(" ")) {
        $value = "$value".replace("`"", "```"")
        $value = "`"$value`""
    }
    $args[$count] = $value
}

$bootstrap = "$PSScriptRoot\bootstrap.ps1"
$env:Path = "$PSScriptRoot\.build-deps\bin;$env:Path"

& $bootstrap

if(!($LastExitCode)) {
    iex "& $command $args"
}
