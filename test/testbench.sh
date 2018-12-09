#!/bin/bash
# echo "testbench started" #comment this out later

chmod 755 bin/*
simulator=$1


#convert mips
rm -rf test/mips_binary #refresh the binaries and remove the old ones
mkdir -p test/mips_binary

mips_parser=test/mips-parser
if [ ! -f $mips_parser/bin/parser ]; then
    make -C $mips_parser parser 2>&1 >/dev/null
fi

output_files=test/output
conversion_log_files="$output_files/mips_conversion_logs.txt"
log_files="$output_files/log_files"
mkdir -p $output_files
mkdir -p $log_files
rm -f $conversion_log_files
assembly_files=test/mips_assembly


for assembly_file in $assembly_files/*
do
    test/mips-parser/bin/parser 2>&1 >>$conversion_log_files $assembly_file 'test/mips_binary/#' 2>&1 >>$conversion_log_files
done


#must be after mips conversion to get all files
binary_files=test/mips_binary
temp_files=test/temp
test_input_file=test/wibble.txt
test_output_csv=$output_files/all_results.csv
temp_stderr_file="$temp_files/tmp_err.txt"
temp_stdout_file="$temp_files/tmp_out.txt"

function extract_info {
    file=$1
    field_to_extract=$2
    IFS=$'\n'
    extracted_info_field="" #nullify variable
    #echo "filename: " $file
    while IFS= read -r line
    do
        if [[ $line == '#'* ]];
        then
            without_hashtag=${line#*#}
            field_from_line=${without_hashtag%:*}
            if [ "$field_from_line" == "$field_to_extract" ];
            then
                #echo extracting $field_from_line
                extracted_info_field=${line#*": "}
            fi
        fi
    done < "$file"
}


function convert_8_bit_dec_to_2s_complement {
    NUMBER="$1"
    converted_result=""
    N_POW=$((2 ** 8))
    NM1_POW=$((2 ** 7))
    if [ $NUMBER -lt $NM1_POW ];
    then
        converted_result=$NUMBER
    else
        converted_result=$(($NUMBER - $N_POW))
    fi
}

function convert_ascii_string_to_decimal {
    ascii=$1
    converted_result=""
    
    while IFS='' read -r -d '' -n 1 char; do
        #decimal=$(printf '%d' "'$char")
        decimal=$(( 16#$(echo -n $char | xxd -p) ))
        # echo $decimal
        converted_result="$converted_result $decimal"
    done < <(printf %s "$ascii")
    converted_result=$(echo $converted_result | xargs) #strip leading and trailing
    
    #converted_result=$(echo -ne $ascii | xxd -p)
    #converted_result=$(echo $(( 16#$hex )))
}

csv_lines=()
mkdir -p $temp_files
rm -f $test_output_csv

if [[ $# -ne 1 ]];
then
    echo "invalid number of command line arguments"
    exit
fi
for binary_file in $binary_files/*
do
    basename=$(basename -- "${binary_file%.*}")
    
    cat $test_input_file | $simulator $binary_file 2>$temp_stderr_file 1>$temp_stdout_file
    exit_code=$?
    convert_8_bit_dec_to_2s_complement $exit_code
    exit_code=$converted_result
    sim_stderr=$(< $temp_stderr_file) #this line needs to be places below exit code for exit code to be correct for some reason
    sim_stdout=$(< $temp_stdout_file)
    convert_ascii_string_to_decimal $sim_stdout
    sim_stdout=$converted_result
    assembly_file="$assembly_files/$basename".s

    #extract info
    extract_info $assembly_file author
    author=$extracted_info_field
    if [[ -z $author ]];
    then
        author=$USER #default value
    fi
    
    
    extract_info $assembly_file expected_output
    expected_output=$extracted_info_field
    
    extract_info $assembly_file expected_exit_code
    expected_exit_code=$extracted_info_field
    
    extract_info $assembly_file extra_info
    extra_info=$extracted_info_field
    
    test_id=$(echo "${basename%%.*}")
    instruction=${test_id//[[:digit:]]/}
    
    debug_message=""
    pass_fail_string="Pass"
    
    if [ -n "${expected_output}" ];
    then
        debug_message="$debug_message | expected output: $expected_output actual output: $sim_stdout"
        if [[ $expected_output != $sim_stdout ]]; then
            pass_fail_string="Fail"
        fi
    fi
    
    if [ $pass_fail_string = "Fail" ];
    then
        expected_exit_code=0 #force it to add exit code if there was output error
    fi
    
    if [ -n "${expected_exit_code}"  ];
    then
        debug_message="$debug_message | expected exit code: $expected_exit_code actual exit code: $exit_code"
        if [[ $expected_exit_code != $exit_code ]]; then
            pass_fail_string="Fail"
        fi
    fi
    
    
    if [ -n "${extra_info}" ];
    then
        debug_message="$debug_message | extra info: $extra_info"
    fi
    
    csv_line="$test_id, $instruction, $pass_fail_string, $author,${debug_message//,} |"
    csv_lines+=($csv_line)
    
    # echo $csv_line > "$log_files/$test_id.txt"
    this_test_log_file="$log_files/$test_id.txt"
    cp -f $temp_stderr_file $this_test_log_file
    echo $csv_line >> $this_test_log_file
    echo $csv_line >> $test_output_csv
    echo "Test conducted on: " $(date '+%d/%m/%Y %H:%M:%S') >> $this_test_log_file
    echo $csv_line
done
# printf '%s\n' "${csv_lines[@]}"
rm -rf $temp_files
# printf '%d\n' "'$sim_stdout" #for printing decimal value of ascii