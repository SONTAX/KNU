#!/usr/bin/ruby
# frozen_string_literal: true

def F(x, a, b, c)
  if x < 3 && b != 0
    a * x**2 - b * x + c
  elsif x > 3 && b.zero?
    (x - a) / (x - c)
  else
    x / c
  end
end

def iterator(a, b, c, cur_x, end_x, dx)
  arr_x = Array.new(0)
  arr_f = Array.new(0)
  ac = a.to_i
  bc = b.to_i
  cc = c.to_i
  while cur_x <= end_x
    arr_x.push(cur_x)
    if ~(ac | bc) & (ac ^ cc) != 0
      arr_f.push(F(cur_x, a, b, c))
    else
      arr_f.push(F(cur_x.to_i, a, b, c))
    end
    cur_x += dx
  end
  [arr_x, arr_f]
end

print "Enter a: \n"
a = gets.chomp.to_f
print "Enter b: \n"
b = gets.chomp.to_f
print "Enter c: \n"
c = gets.chomp.to_f
print "Enter Xbeg: \n"
beg_x = gets.chomp.to_f
print "Enter Xend: \n"
end_x = gets.chomp.to_f
print "Enter dX: \n"
dx = gets.chomp.to_f
x_array, f_array = iterator(a, b, c, beg_x, end_x, dx)
print x_array
puts ''
print f_array
puts
