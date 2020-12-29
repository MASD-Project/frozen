# Copyright (C) 2012-2016 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be  useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#

param (
    [string]$build_type = "Release",
    [string]$compiler = "msvc",
    [string[]]$target = @()
)

function Get-ScriptDirectory {
    $Invocation = (Get-Variable MyInvocation -Scope 1).Value;
    Split-Path $Invocation.MyCommand.Path;
}

#
# Root directory for the product.
#
$dir=Get-ScriptDirectory;
$product_dir="${dir}\..\..";
write-host "* Product directory: ${product_dir}";

#
# Compiler
#
if ($compiler -eq "msvc") {
    $generator="Visual Studio 15 2017 Win64";
    write-host "* compiler: ${compiler}";
} elseif ($compiler -eq "clang-cl") {
    $generator="Ninja";
    write-host "* compiler: ${compiler}";
} else {
    write-host "* Unrecognised compiler: ${compiler}";
    exit 1
}

#
# Target
#
write-host "* Target: '${target}'";

#
# Setup directories
#
$output_dir="${product_dir}/build/output";
if (!(Test-Path -Path $output_dir)) {
    New-Item -ItemType directory -Path $output_dir | Out-Null
}

$compiler_dir="${output_dir}/${compiler}";
if (!(Test-Path -Path $compiler_dir)) {
    New-Item -ItemType directory -Path $compiler_dir | Out-Null
}

$build_type_dir="${compiler_dir}/${build_type}";
if (!(Test-Path -Path $build_type_dir)) {
    New-Item -ItemType directory -Path $build_type_dir | Out-Null
}

Set-Location -Path ${build_type_dir} | Out-Null
Write-Host "Build directory: ${build_type_dir}"

#
# CMake setup
#
$cmake_defines="-DCMAKE_BUILD_TYPE=${build_type}"
$cmake_defines="${cmake_defines} -DWITH_LATEX=OFF"
$cmake_defines="${cmake_defines} -DWITH_MINIMAL_PACKAGING=ON"

# Handle vcpkg.
if (Test-Path env:CMAKE_TOOLCHAIN_FILE) {
    $toolchain_file=$env:CMAKE_TOOLCHAIN_FILE
    $cmake_defines="${cmake_defines} -DCMAKE_TOOLCHAIN_FILE=${toolchain_file}"
    $cmake_defines="${cmake_defines} -DVCPKG_TARGET_TRIPLET=x64-windows-static"
}

# Handle clang-cl
if ($compiler -eq "clang-cl") {
    $cmake_defines="${cmake_defines} -DCMAKE_C_COMPILER=clang-cl"
    $cmake_defines="${cmake_defines} -DCMAKE_CXX_COMPILER=clang-cl"
}

#
# Build
#
write-host "* Starting build.";
$command = "cmake ${cmake_defines} -G '${generator}' ${product_dir}";
Invoke-Expression -Command $command
if ($LastExitCode -ne 0) {
    write-host "Error whilst configuring. Command: $command"
    exit 1
}

$targets = $target -split " ";
foreach ($element in $targets) {
    $command = "cmake --build . --config $build_type --target ${element}";
    Invoke-Expression -Command $command
    if ($LastExitCode -ne 0) {
        write-host "Error whilst running target ${target}."
        exit 1
    }
}
