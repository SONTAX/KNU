#!/usr/bin/ruby
# frozen_string_literal: true

# 3

#   3)
def factorial(num)
  num > 1 ? num * factorial(num - 1) : 1
end

def task3(num)
  n = gets.chomp.to_i
  while (n < 2) || (n > 10) do
    puts 'Wrong number'
    n = gets.chomp.to_i
  end
  sum = 1
  (1..num).each do |i|
    sum += (num**i) / factorial(i)
  end
end

puts '3): ', task3(10)

#   4)
def task4(num)
  sum = 0
  (1..num).each do |i|
    subsumes = 0
    (1..i).each do |j|
      subsumes += Math.sin(j)
    end
    sum += 1 / subsumes
  end
  sum
end

puts '4): ', task4(10)

