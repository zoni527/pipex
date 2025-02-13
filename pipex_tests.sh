#!/bin/zsh
echo "----------------------------------------------------"
echo
echo "< '' '' | '' > ''"
< '' cat | ls > ''
echo $?
echo
echo "----------------------------------------------------"
echo
echo "./pipex '' '' '' ''"
./pipex '' '' '' ''
echo $?
echo
echo "----------------------------------------------------"
echo
echo "< in cat | cat > out"
< in cat | cat > out
echo $?
rm out
echo
echo "----------------------------------------------------"
echo
echo "./pipex in cat cat out"
./pipex in cat cat out
echo $?
rm out
echo
echo "----------------------------------------------------"
echo
echo "< in asd | asd > out"
< in asd | asd > out
echo $?
echo
echo "----------------------------------------------------"
echo
echo "./pipex in asd asd out"
./pipex in asd asd out
echo $?
echo
echo "----------------------------------------------------"
echo "Creating folder indir"
mkdir -p indir
echo "----------------------------------------------------"
echo
echo "< indir ls | wc > shell_outfile"
< indir ls | wc > shell_outfile
echo $?
echo "Contents of shell_outfile:"
cat shell_outfile
echo
echo "----------------------------------------------------"
echo
echo "./pipex indir ls wc pipex_outfile"
./pipex indir ls wc pipex_outfile
echo $?
echo "Contents of pipex_outfile:"
cat pipex_outfile
echo
echo "----------------------------------------------------"
echo "Creating infile"
echo "I am an infile" > infile
echo "----------------------------------------------------"
echo "Contents of infile:"
echo
cat infile
echo
echo "----------------------------------------------------"
echo
echo "< infile cat | tr ' ' '|' > shell_outfile"
< infile cat | tr ' ' '|' > shell_outfile
echo $?
echo "Contents of shell_outfile:"
cat shell_outfile
echo
echo "----------------------------------------------------"
echo
echo "./pipex infile cat \"tr ' ' '|'\" pipex_outfile"
./pipex infile cat "tr ' ' '|'" pipex_outfile
echo $?
echo "Contents of pipex_outfile:"
cat pipex_outfile
echo
echo "----------------------------------------------------"
echo "Removing permissions of infile"
chmod 0 infile
echo "----------------------------------------------------"
echo "Adding permissions of infile"
chmod 777 infile
echo "----------------------------------------------------"
