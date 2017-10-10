require 'colorize'

$params = {}


ARGV.each do |arg|
  v = arg.split('=')
  $params[v[0]] = v[1]
end



def replace sym
  if $params.key?(sym)
    puts "[OK] Found key: #{sym}".green
  else
    puts "[ERROR] Missing key: #{sym}".red 
  end
  $params[sym]
end

def generateFile(mode = ".h")
  s = ""
  f = File.open("state" + mode, "r")
  f.each_line do |line|
    s += line.gsub(/<%= .*? %>/) {|sym| "#{replace(sym[3..-3].strip)}"}
  end
  f.close

  g = File.open($params["name"] + "State" + mode, "w" )
  g.write(s)
  g.close
end


generateFile(".h")
generateFile(".cpp")

puts "Move files to XCODE project and add header to states.h".blue
