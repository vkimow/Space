param (
    [switch] $Clear
)

$ScriptPath = split-path -parent $MyInvocation.MyCommand.Definition
$CurrentPath = Get-Location

function ClearDirectories{
    Write-Host "Clear directories"
    if (Test-Path -Path .\bin) {
        Write-Host "Clear bin directory"
        Remove-Item -Path bin/ -Recurse -Force -Confirm:$false
    }

    if (Test-Path -Path project) {
        Write-Host "Clear project directory"
        Remove-Item -Path .\project\* -Recurse -Force
    }
}
function BuildSolution {
    if (!(Test-Path -Path project)) {
        Write-Host "Create project directory"
        New-Item -ItemType Directory -Path project
    }

    Write-Host "Build solution"
    & cmake . -B project
    Write-Host "Solution has been built"
}

Set-Location $ScriptPath
Set-Location -Path .. -PassThru
if($Clear) {
    ClearDirectories
}
BuildSolution
Set-Location $CurrentPath