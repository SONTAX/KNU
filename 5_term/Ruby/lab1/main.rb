# frozen_string_literal: true

print "Enter phi: \n"
phi = gets.chomp.to_f
print "Enter a: \n"
a = gets.chomp.to_f
print "Enter x: \n"
x = gets.chomp.to_f
print "Enter t: \n"
t = gets.chomp.to_f
pi = Math.atan2(0.0, -1.0)
ctg_argument = ((Math.log(phi) + 16.3) / Math.sqrt(Math.exp(x) - a**(3 / 2))).abs
my_f = Math.cos(ctg_argument) / Math.sin(ctg_argument) + (6.8 + Math.cos(pi - t**2)) / Math.sin(a)**3
print "pi: #{pi}\nF: #{my_f}\n"
