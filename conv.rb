#!/usr/bin/ruby

f_out_name = 'collected.cpp'
f_in_name = 'main.cpp'

program_string = ''
program_string_string = ''
middle_stuff = ''
middle_stuff += "string program_str = \"\"\n"

f_in = File.open(f_in_name, 'r')
f_in.each do |line|
  program_string += line

  line = line.chomp
  line = line.gsub('\\', '\\\\\\')
  line = line.gsub("\"", "\\\"")

  program_string_string += "\"" + line + "\\n\"" + "\n"
end
program_string_string += ";"

f_out = File.open(f_out_name, 'w')
f_out.write program_string + middle_stuff + program_string_string
