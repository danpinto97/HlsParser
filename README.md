# HlsParser
C++ project for downloading, parsing, and sorting HLS files
Documentation used: https://developers.broadpeak.io/docs/foundations-hls

# Building
To build, open the solution file in Visual Studios (I used 2022) and build. This was built using C++ 14.

# Usage
Run the HlsParser executable
This will download the HLS file to your computer and start a command prompt UI.\
The command prompt will ask you to input a command to sort. After sorting, the sorted type will now print.\
The command style is as follows:\
`<type>:<field>:<asc_or_desc>` 
##
The following sorting commands are currently supported:\
`video:bandwidth:asc`\
`video:bandwidth:desc`\
`video:avgbandwidth:asc`\
`video:avgbandwidth:desc`\
`video:framerate:asc`\
`video:framerate:desc`\
`image:bandwidth:asc`\
`image:bandwidth:desc`\
`audio:language:asc`\
`audio:language:desc`\
`audio:name:asc`\
`audio:name:desc`\
`audio:group:asc`\
`audio:group:desc`
