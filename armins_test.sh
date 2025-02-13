#!/bin/zsh

rm -Rf input not_working_input output output2 not_working_output output3 output4 test.sh not_working_test.sh permissions_denied_test.sh directory

# ANSI color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
function run_test() {
    local test_name="$1"
    local command="$2"
	local kitten="$3"

    echo "${YELLOW}Running test: ${BLUE}$test_name${NC}"
    echo "${YELLOW}This is the command: ${BLUE}$command${PURPLE}"
    eval "$command"
	exit_code=$?
	echo "${YELLOW}Exit value: $exit_code${NC}"
	if [ -n "$kitten" ]; then
		echo "${YELLOW}Now let us do: cat ${BLUE}$kitten${PURPLE}"
    	cat "$kitten"
	fi
	echo "${BLUE}------------------------------------------------------------------------------------------------------------------------------------------------------------${NC}"
	while true; do
		printf "${YELLOW}Do you want to continue to the next test? (y/n): ${NC}" 
    	read answer
    	case $answer in
        	[Yy]* ) break;;
        	[Nn]* )
				echo "${RED}Aww I'm sad to see you go! Exitting now...${NC}"
				 rm -Rf input not_working_input output output2 not_working_output output3 output4 test.sh not_working_test.sh permissions_denied_test.sh directory
				exit 0;;
        	* ) echo "${RED}Please enter 'y' for yes or 'n' for no.${NC}";;
    esac
done
}

# Create input files
echo "This is a test input file." > input
echo "Another test input." > not_working_input
echo "hello" >> input
echo "hello" >> input
echo "hello" >> input
echo "goodbye" >> input

chmod 000 not_working_input

# Create output files
touch output output2 not_working_output
chmod 000 not_working_output

# Create executable files
touch test.sh not_working_test.sh permissions_denied_test.sh not_working
chmod 777 test.sh
chmod 777 not_working_test.sh
chmod 777 not_working
echo "#!/bin/bash" > test.sh
echo "ls" >> test.sh
echo "ls" > not_working_test.sh
echo -e "\x00\x00\x00\x00\x00\x00\x00\x00" > not_working

# Create directories
mkdir directory

# Make the library

make re
make clean

# Test case: Ensure pipex takes exactly 5 inputs
run_test "Test case: Ensure pipex takes exactly 5 inputs" "./pipex 1 2 3"
run_test "Test case: Ensure pipex takes exactly 5 inputs" "./pipex 1 2 3 4 5"

# Test case: Basic test
run_test "Test case: Basic test" "./pipex input 'ls -l' cat output" "output"
run_test "Versus the terminal" "< input ls -l | cat > output2" "output2"

# Test case: Basic test 2: What if there is no input file?
run_test "Test case: Basic test 2: What if there is no input file?" "./pipex input_wrong 'ls -l' 'echo hello' output" "output"
run_test "Versus the terminal" "< input_wrong ls -l | echo hello > output2" "output2"

# Test case: Basic test 3: What if there is no output file?
run_test "Test case: Basic test 3: What if there is no output file?" "./pipex input 'ls -l' 'echo hello' output3" "output3"
run_test "Versus the terminal" "< input ls -l | echo hello > output4" "output4"

# Test case: Basic test 4: Let's try a few different commands!
run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'grep hello' 'cat' output" "output"
run_test "Versus the terminal" "< input grep hello | cat > output2" "output2"

run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'grep goodbye' 'cat' output" "output"
run_test "Versus the terminal" "< input grep goodbye | cat > output2" "output2"

run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'grep goodbye' 'wc -l' output" "output"
run_test "Versus the terminal" "< input grep goodbye | wc -l > output2" "output2"

run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'grep hello' 'wc -l' output" "output"
run_test "Versus the terminal" "< input grep hello | wc -l > output2" "output2"

run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'ls -l' 'wc -l' output" "output"
run_test "Versus the terminal" "< input ls -l | wc -l > output2" "output2"

# Test case: Basic test 5: What if I include the path to the function directly?
run_test "Test case: Basic test 5: What if I include the path to the function directly?" "./pipex input /bin/ls cat output" "output"
run_test "Versus the terminal" "< input /bin/ls | cat > output2" "output2"

# Test case: Basic test 6: What happens if we include command options while including the path directly?
run_test "Test case: Basic test 6: What happens if we include command options while including the path directly?" "./pipex input '/bin/ls -l' cat output" "output"
run_test "Versus the terminal" "< input /bin/ls -l | cat > output2" "output2"

echo "${GREEN}That concludes the basic tests!${NC}"
echo "${PURPLE}------------------------------------------------------------------------------------------------------------------------------------------------------------"

	while true; do
		printf "${CYAN}Do you want to try the extreme tests? (y/n): ${NC}" 
    	read answer
    	case $answer in
        	[Yy]* ) break;;
        	[Nn]* )
				echo "${RED}Fearing failure and avoiding challenges only delays the inevitable. Embrace the tests, for they are the stepping stones to mastery and success. It's through overcoming challenges that we truly learn and grow.${NC}"
				 rm -f input not_working_input output output2 not_working_output output3 output4 test.sh not_working_test.sh permissions_denied_test.sh
				exit 0;;
        	* ) echo "${RED}Please enter 'y' for yes or 'n' for no.${NC}";;
    esac
done


# Extreme test 1: What happens if you try an input file whose permissions you do not have?
run_test "Extreme test 1: What happens if you try an input file whose permissions you do not have?" "./pipex not_working_input 'ls' 'echo hello2' output" "output"
run_test "Versus the terminal" "< not_working_input ls | echo hello3 > output2" "output2"

# Extreme test 2: What happens if you try an output file whose permissions you do not have?
run_test "Extreme test 2: What happens if you try an output file whose permissions you do not have?" "./pipex input 'ls' 'echo hello7' not_working_output" "not_working_output"
run_test "Versus the terminal" "< input ls | echo hello17 > not_working_output" "not_working_output"

# Extreme test 3: What happens if we change permissions while doing the pipe?
run_test "Extreme test 3: What happens if we change permissions while doing the pipe?" "./pipex input 'chmod 000 output' 'echo wow' output" "output"
chmod 777 output
echo "${BLUE}I just changed the outputs permissions back to 777 so that we can see whats inside"
cat output
run_test "Versus the terminal" "< input chmod 000 output2 | echo 'wow it still does it!' > output2" "output2"
chmod 777 output2
echo "${BLUE}I just changed the output2s permissions back to 777 so that we can see whats inside"
cat output2

# Extreme test 5: Can you handle executables not located within the path env variable?
run_test "Extreme test 5: Can you handle executables not located within the path env variable?" "./pipex input ./test.sh cat output" "output"
run_test "Versus the terminal" "< input ./test.sh | cat > output2" "output2"

# Extreme test 6: Can you handle executables not located within the path env variable that you also do not have permission to use?
run_test "Extreme test 6: Can you handle executables not located within the path env variable that you also do not have permission to use?" "./pipex input ls ./permissions_denied_test.sh output" "output"
run_test "Versus the terminal" "< input ls | ./permissions_denied_test.sh > output2" "output2"

# Extreme test 7: Can you handle executables not located within the path env variable that also do not work with execve?
run_test "Extreme test 7: Can you handle executables not located within the path env variable that also do not work with execve?" "./pipex input ls ./not_working_test.sh  output" "output"
run_test "Versus the terminal" "< input ls | ./not_working_test.sh > output2" "output2"

# Extreme test 8: Can you handle being given directories instead of executables?
run_test "Extreme test 8: Can you handle being given directories instead of executables?" "./pipex input ./directory ./directory output"
run_test "Versus the terminal" "< input ./directory | ./directory > output2"

# Extreme test 9: Can you handle when the given commands are empty?
run_test "Extreme test 9: Can you handle when the given commands are empty?" "./pipex input '' '' output"
run_test "Versus the terminal" "< input '' | '' > output"

# Extreme test 10: Can you handle when everything is empty?
run_test "Extreme test 10: Can you handle when everything is empty?" "./pipex '' '' '' ''"
run_test "Versus the terminal" "< '' '' | '' > ''"

# Extreme test 11: Can you handle a not working executable file?
run_test "Extreme test 11: Can you handle a not working executable file?" "./pipex input ./not_working ./not_working output"
run_test "Versus the terminal" "< input ./not_working | ./not_working > output"

# Extreme test 12: Can you handle a file  that you do have access to and is executable but that does not have the path to it but instead is inside of the same directory?
run_test "# Extreme test 12: Can you handle a file  that you do have access to and is executable but that does not have the path to it but instead is inside of the same directory?" "./pipex input test.sh test.sh output" "output"
run_test "Versus the terminal" "< input test.sh | test.sh > output2" "output2" 

echo "Thats it for all the extreme cases. Now lets handle an environment that does not contain the PATH variable!"
# Clean up temporary files
rm -Rf input not_working_input output output2 not_working_output output3 output4 test.sh not_working_test.sh permissions_denied_test.sh directory
make fclean
