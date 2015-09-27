#!/usr/bin/ruby

out_name = 'compiled.cpp'
main_in_name = 'main.cpp'
replicator_in_name = 'replicator.h'

main_program_string = ''
main_program_string_string = ''
replicator_program_string = ''
replicator_program_string_string = ''
main_middle_stuff = "string program_str = \"\"\n"
replicator_middle_stuff = "string replicator_str = \"\"\n"

#copy main file and append string version
main_in = File.open(main_in_name, 'r')
main_in.each do |line|
  main_program_string += line

  line = line.chomp
  line = line.gsub('\\', '\\\\\\')
  line = line.gsub("\"", "\\\"")

  main_program_string_string += "\"" + line + "\\n\"" + "\n"
end
main_program_string_string += ";\n"

#copy replicator file and append string version
replicator_in = File.open(replicator_in_name, 'r')
replicator_in.each do |line|
  replicator_program_string += line

  line = line.chomp
  line = line.gsub('\\', '\\\\\\')
  line = line.gsub("\"", "\\\"")

  replicator_program_string_string += "\"" + line + "\\n\"" + "\n"
end
replicator_program_string_string += ";\n"

out = File.open(out_name, 'w')
out.write replicator_program_string + replicator_middle_stuff + replicator_program_string_string
out.write main_program_string + main_middle_stuff + main_program_string_string
