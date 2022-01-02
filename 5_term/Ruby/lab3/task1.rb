#!/usr/bin/ruby
# frozen_string_literal: true

# 1

#   a
a = true
b = false
c = false
x = 4
y = 120
z = -20
puts 'a: ', !(a || b) && (a || !b)
puts 'b: ', (z != y) <=> (y <= 6) && a || b && c && x >= 1.5
puts 'c: ', (8 - x * 2 <= z) && (x**2 != y**2) || (z >= 15)
puts 'd: ', x.positive? && y.negative? || z >= (x * y - (-y / x)) + -z
puts 'e: ', !(a || b && !(c || (!a || b)))
puts 'f: ', x**2 + y**2 >= 1 && x >= 0 && y >= 0
puts 'g: ', (a && (c && b != b || a) || c) && b

#   b
x = 7
p = false
puts (Math.log(x) < x) && !p && (Math.sqrt(x) > x * x) || (2 * x == x)
