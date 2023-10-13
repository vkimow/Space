param (
    [switch] $Clear
)

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
}

if($Clear) {
    ClearDirectories
}
BuildSolution
