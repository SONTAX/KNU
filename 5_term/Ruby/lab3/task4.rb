#!/usr/bin/ruby
# frozen_string_literal: true

def factorial(num)
  num > 1 ? num * factorial(num - 1) : 1
end

# 4

def task1
  prev = 1.0
  sum = 0.0
  n = 2
  eps = 0.00001
  while prev > eps
    prev = (factorial(n - 1).to_f / factorial(n + 1))**(n * (n + 1))
    sum += prev
    n += 1
  end
  sum
end

def task2(num)
  prev = 1.0
  sum = 0.0
  n = 0
  eps = 0.00001
  while prev > eps
    prev = ((num - 1)**(2 * n + 1)).to_f / ((2 * n + 1) * ((num + 1)**(2 * n + 1)))
    sum += prev
    n += 1
  end
  2 * sum
end

def task3
  prev = 1.0
  sum = 0.0
  n = 1
  eps = 0.00001
  while prev > eps
    prev = (factorial(2 * n - 1) * factorial(3 * n - 1)).to_f / (factorial(4 * n) * (3**(2 * n)) * factorial(2 * n))
    sum += prev
    n += 1
  end
  sum
end

x = 12
temp = task2(x)
puts '1): ', task1
puts 'computed: ', temp, 'expected: ', Math.log(x), 'difference with expected is: ', (temp - Math.log(x)).abs
puts '3): ', task3
