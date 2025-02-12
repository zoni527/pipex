#!/bin/zsh
echo "< '' '' | '' > ''"
< '' cat | ls > ''
echo $?
echo "----------------------------------------------------"
echo "./pipex '' '' '' ''"
./pipex '' '' '' ''
echo $?
echo "----------------------------------------------------"
echo "< indir ls | wc > shell_outfile"
< indir ls | wc > shell_outfile
echo $?
echo "Contents of shell_outfile:"
cat shell_outfile
echo "----------------------------------------------------"
echo "./pipex indir ls wc pipex_outfile"
./pipex indir ls wc pipex_outfile
echo $?
echo "Contents of pipex_outfile:"
cat pipex_outfile
echo "----------------------------------------------------"
echo "./pipex '' '' '' ''"
./pipex '' '' '' ''
echo $?
echo "----------------------------------------------------"
echo "Contents of infile:"
cat infile
echo "----------------------------------------------------"
echo "< infile cat | tr ' ' '|' > shell_outfile"
< infile cat | tr ' ' '|' > shell_outfile
echo $?
echo "Contents of shell_outfile:"
cat shell_outfile
echo "----------------------------------------------------"
echo "./pipex infile cat \"tr ' ' '|'\" pipex_outfile"
./pipex infile cat "tr ' ' '|'" pipex_outfile
echo $?
echo "Contents of pipex_outfile:"
cat pipex_outfile
echo "----------------------------------------------------"
