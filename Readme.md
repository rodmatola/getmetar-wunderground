# Get METAR
#### from Weather Underground

This job is for to get METAR (METeorological Aerodrome Report) data from a large period from [Weather Underground](https://www.wunderground.com/) site.

## How to use

On a Linux terminal execute

`./getmetar`

and follow the instructions (in portuguese). If you don't have permission to excecute type

`sudo chmod +x getmetar`

You need to have a folder named `bin` to run.

## How it works

The `src` folder contains the C source code that generates a file with `wget` instructions for download data from a URL. If the URL changes, you need to update the source, at the end of the source, with the correct URL (last used in October 29, 2016).

> The URL changed, but I don't know the new one yet. As it is, will save empty files.

The job will generate an executable and a script inside `bin` folder, a folder named with the initials of aerodrome chosen (eg. SBGL) with one file for each day of the chosen period.

