#!/usr/bin/ruby
# frozen_string_literal: true

# 5

N = 11.0
C = 7.0
PI = 3.141

#   1)
def y(num)
  (((num**(2 / C) + N**(2 / C))**2 - 4 * num**(2 / C + 2 / N)) /
                  (num**(1 / N) - num**(1 / C))**2 + 3 * num**(1 / N + 1 / C))**(1 / 2) +
    (num**2 + 2 * num - 4) / (C + num)
end

def task1
  x = 1.0
  func = 0.0
  delta = (N - 1) / (N + C)
  (0..(N + C)).each do |_i|
    printf "x: #{x}\ny: #{y(x)}\n"
    func += y(x)
    x += delta
  end
  func
end

#   2)
def z(num)
  (((Math.sin(num)**2 + Math.tan(num)**2)**C + 1) * (Math.cos(num)**2 - (Math.cos(num) / Math.sin(num))**2 + 1)) /
    ((Math.cos(num)**2 + (Math.cos(num) / Math.sin(num))**2 + 1) * (Math.sin(num)**2 + Math.tan(num)**2) - 1)
end

def task2
  x = PI / N
  func = 0.0
  delta = (PI - PI / N) / (1.5 * N + C)
  while x <= PI
    printf "x: #{x}\nz: #{z(x)}\n"
    func += z(x)
    x += delta
  end
  func
end

#   3)
def f(num)
  if num > 2 && num < N
    y(num)
  elsif num > N && num < (2 * N)
    z(num)
  else
    y(num) + z(num)
  end
end

def task3
  x = 2.0
  func = 0.0
  delta = (C - 2) / (2 * N)
  (0..(2 * N)).each do |_i|
    printf "x: #{x}\nf: #{f(x)}\n"
    func += f(x)
    x += delta
  end
  func
end

puts '1)', ''
puts '', 'total:', task1
puts '', '', '', '', '2)', ''
puts '', 'total:', task2
puts '', '', '', '', '3)', ''
puts '', 'total:', task3
