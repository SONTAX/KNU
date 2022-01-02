#!/usr/bin/ruby
# frozen_string_literal: true

require 'matrix'

def matrix_print(matrix)
  matrix_ = Matrix[*matrix]
  puts matrix_.to_a.map(&:inspect)
end

temp_a = (0..19_900).map { Array.new 20_000 }
temp_b = (0..19_900).map { Array.new 20_000 }
temp_x = Array.new 20_000
temp_y = Array.new 20_000

(0..19_900).each do |i|
  (0..19_900).each do |j|
    temp_a[i][j] = rand(10)
    temp_b[i][j] = rand(10)
    temp_a[i][j] = 1 if i == j
  end
  temp_x[i] = rand(10)
  temp_y[i] = rand(10)
end

a = Matrix[*temp_a]
b = Matrix[*temp_b]
x = Vector[*temp_x]
y = Vector[*temp_y]

def task1(matrix, number)
  temp = Array.new(matrix.size) do |i|
    Array.new(matrix[0].size) do |j|
      matrix[i][j] * number
    end
  end
  Matrix[*temp]
end

def task2(matrix1, matrix2)
  temp = Array.new(matrix1.size) do |i|
    Array.new(matrix2[0].size) do |j|
      matrix1[i][j] + matrix2[i][j]
    end
  end
  Matrix[*temp]
end

def task3(matrix)
  temp = Array.new(matrix[0].size) do |i|
    Array.new(matrix.size) do |j|
      matrix[j][i]
    end
  end
  Matrix[*temp]
end

def task4(matrix1, matrix2)
  temp = Array.new(matrix1.size) do |i|
    Array.new(matrix2[0].size) do |j|
      matrix2.size.times.inject(0) { |result, k| result + matrix1[i][k] * matrix2[k][j] }
    end
  end
  Matrix[*temp]
end

def task5(matrix)
  matrix.size.times.inject(0) { |result, i| result + matrix[i][i] }
end

def task6(vector1, vector2)
  temp = Array.new(vector1.size) do |i|
    vector1[i] * vector2[i]
  end
  Vector[*temp]
end

matrix1 = task1(b.to_a, 2)
matrix2 = task2(a.to_a, b.to_a)
matrix3 = task3(a.to_a)
matrix4 = task4(a.to_a, b.to_a)
trace5 = task5(b.to_a)
vector6 = task6(x.to_a, y.to_a)

puts 'A: '
matrix_print(a)
puts 'B: '
matrix_print(b)
puts 'X: ', x
puts 'Y: ', y
puts 'task1: '
matrix_print(matrix1)
puts 'task2: '
matrix_print(matrix2)
puts 'task3: '
matrix_print(matrix3)
puts 'task4: '
matrix_print(matrix4)
puts 'task5: ', trace5
puts 'task6: ', vector6
puts 'det: ', a.det, 'trace: ', a.tr
