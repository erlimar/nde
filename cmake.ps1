#Requires -Version 2

for($count = 0; $count -lt $args.length; $count++) {
    $value = $args[$count]
    if("$value".contains(" ")) {
        $value = "$value".replace("`"", "```"")
        $value = "`"$value`""
    }
    $args[$count] = $value
}

$env:Path = "$pwd\.build-deps\bin;$env:Path"

iex "& cmake $args"
