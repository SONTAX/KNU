import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.Random;
import java.util.concurrent.TimeUnit;

public class Equation {
    private static final int dim = 20;
    private static final int precision = 100;
    private static final Random random = new Random();
    private BigDecimal[][] A = new BigDecimal[dim][dim];
    private BigDecimal[] b = new BigDecimal[dim];
    private final BigDecimal[] expectedX = new BigDecimal[dim];
    private final BigDecimal[] x = new BigDecimal[dim];
    private final BigDecimal[] xNew = new BigDecimal[dim];

    public Equation() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                this.A[i][j] = BigDecimal.ZERO;
            }
            this.b[i] = BigDecimal.ZERO;
            this.x[i] = BigDecimal.ZERO;
            this.expectedX[i] = BigDecimal.ZERO;
        }
        /*A[0][0] = new BigDecimal(2);
        A[0][1] = new BigDecimal(1);
        A[0][2] = new BigDecimal(0);
        A[0][3] = new BigDecimal(0);
        A[1][0] = new BigDecimal(1);
        A[1][1] = new BigDecimal(10);
        A[1][2] = new BigDecimal(-5);
        A[1][3] = new BigDecimal(0);
        A[2][0] = new BigDecimal(0);
        A[2][1] = new BigDecimal(1);
        A[2][2] = new BigDecimal(-5);
        A[2][3] = new BigDecimal(2);
        A[3][0] = new BigDecimal(0);
        A[3][1] = new BigDecimal(0);
        A[3][2] = new BigDecimal(1);
        A[3][3] = new BigDecimal(4);
        b[0] = new BigDecimal(-5);
        b[1] = new BigDecimal(-18);
        b[2] = new BigDecimal(-40);
        b[3] = new BigDecimal(-27);
        expectedX[0] = new BigDecimal(-3);
        expectedX[1] = new BigDecimal(1);
        expectedX[2] = new BigDecimal(5);
        expectedX[3] = new BigDecimal(-8);*/
    }

    private void bCalculation() {
        for (int i = 0; i < dim; i++) {
            this.b[i] = BigDecimal.ZERO;
            for (int j = 0; j < dim; j++) {
                this.b[i] = this.b[i].add(this.A[i][j].multiply(this.expectedX[j]));
            }
        }
    }

    public void RandomMatrix() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                this.A[i][j] = new BigDecimal(random.nextInt(3) + 1);
            }
            this.expectedX[i] = BigDecimal.valueOf(Math.random() * 4 - 2);
        }
        bCalculation();
    }

    public void RandomDiagonallyDominantMatrix() {
        for (int i = 0; i < dim; i++) {
            BigDecimal temp = BigDecimal.ZERO;
            for (int j = 0; j < dim; j++) {
                this.A[i][j] = new BigDecimal(random.nextInt(3) + 1);
                if (i != j) {
                    temp = temp.add(A[i][j]);
                }
            }
            this.A[i][i] = temp.add(BigDecimal.ONE);
            this.expectedX[i] = BigDecimal.valueOf(Math.random() * 4 - 2);
        }
        bCalculation();
    }

    public void RandomThreeDiagonalMatrix() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                this.A[i][j] = BigDecimal.ZERO;
            }
        }
        for (int i = 0; i < dim; i++) {
            if (i == 0) {
                this.A[i][i + 1] = new BigDecimal(random.nextInt(3) + 1);
                this.A[i][i] = A[i][i + 1].add(new BigDecimal(random.nextInt(3) + 1));
            } else if (i == dim - 1) {
                this.A[i][i - 1] = new BigDecimal(random.nextInt(3) + 1);
                this.A[i][i] = A[i][i - 1].add(new BigDecimal(random.nextInt(3) + 1));
            } else {
                this.A[i][i - 1] = new BigDecimal(random.nextInt(3) + 1);
                this.A[i][i + 1] =new BigDecimal(random.nextInt(3) + 1);
                this.A[i][i] = A[i][i - 1].add(A[i][i + 1].add(new BigDecimal(random.nextInt(3) + 1)));
            }
            this.expectedX[i] = BigDecimal.valueOf(Math.random() * 4 - 2);
        }
        bCalculation();
    }

    public void RandomThreeDiagonalHilbertMatrix() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                this.A[i][j] = BigDecimal.ZERO;
            }
        }
        for (int i = 0; i < dim; i++) {
            BigDecimal divide = BigDecimal.ONE.divide(new BigDecimal(i + 1)
                    .add(new BigDecimal(i + 1).add(BigDecimal.ONE.negate())), precision, RoundingMode.HALF_UP);
            BigDecimal divide2 = BigDecimal.ONE.divide(new BigDecimal(i + 1)
                    .add(new BigDecimal(i + 2).add(BigDecimal.ONE.negate())), precision, RoundingMode.HALF_UP);
            if (i == 0) {
                this.A[i][i] = divide;
                this.A[i][i + 1] = divide2;
            } else {
                BigDecimal divide1 = BigDecimal.ONE.divide(new BigDecimal(i + 1)
                        .add(new BigDecimal(i).add(BigDecimal.ONE.negate())), precision, RoundingMode.HALF_UP);
                if (i == dim - 1) {
                    this.A[i][i - 1] = divide1;
                    this.A[i][i] = divide;
                } else {
                    this.A[i][i - 1] = divide1;
                    this.A[i][i] = divide;
                    this.A[i][i + 1] = divide2;
                }
            }
            this.expectedX[i] = BigDecimal.valueOf(Math.random() * 4 - 2);
        }
        bCalculation();
    }

    public void RandomHilbertMatrix() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                this.A[i][j] = BigDecimal.ONE.divide(new BigDecimal(i + 1)
                        .add(new BigDecimal(j + 1).add(BigDecimal.ONE.negate())), precision, RoundingMode.HALF_UP);
            }
            this.expectedX[i] = BigDecimal.valueOf(Math.random() * 4 - 2);
        }
        bCalculation();
    }

    private BigDecimal[][] MatrixMultiplication(BigDecimal[][] left, BigDecimal[][] right) {
        BigDecimal[][] result = new BigDecimal[dim][dim];
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                result[i][j] = BigDecimal.ZERO;
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                for (int k = 0; k < dim; k++) {
                    result[i][j] = result[i][j].add(left[i][k].multiply(right[k][j]));
                }
            }
        }
        return result;
    }

    private BigDecimal[] VectorMultiplication(BigDecimal[][] matrix, BigDecimal[] vector) {
        BigDecimal[] result = new BigDecimal[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = BigDecimal.ZERO;
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                result[i] = result[i].add(matrix[i][j].multiply(vector[j]));
            }
        }
        return result;
    }

    private BigDecimal[][] MatrixE() {
        BigDecimal[][] result = new BigDecimal[dim][dim];
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (i == j) {
                    result[i][j] = BigDecimal.ONE;
                } else {
                    result[i][j] = BigDecimal.ZERO;
                }
            }
        }
        return result;
    }

    private BigDecimal[][] MatrixP(int currentIndex, int mainIndex) {
        BigDecimal[][] result = MatrixE();
        BigDecimal temp = b[currentIndex];
        b[currentIndex] = b[mainIndex];
        b[mainIndex] = temp;
        result[currentIndex][currentIndex] = BigDecimal.ZERO;
        result[mainIndex][mainIndex] = BigDecimal.ZERO;
        result[mainIndex][currentIndex] = BigDecimal.ONE;
        result[currentIndex][mainIndex] = BigDecimal.ONE;
        return result;
    }

    private BigDecimal[][] MatrixM(int index) {
        BigDecimal[][] result = MatrixE();
        result[index][index] = BigDecimal.ONE.divide(A[index][index], precision, RoundingMode.HALF_UP);
        for (int i = index + 1; i < dim; i++) {
            result[i][index] = A[i][index].negate().divide(A[index][index], precision, RoundingMode.HALF_UP);
        }
        return result;
    }

    private BigDecimal SumRightJ(int start) {
        BigDecimal result = BigDecimal.ZERO;
        for (int i = (start + 1); i < dim; i++) {
            result = result.add(A[start][i].multiply(x[i]));
        }
        return result.negate();
    }

    private BigDecimal SumLeftJ(int end) {
        BigDecimal result = BigDecimal.ZERO;
        for (int i = 0; i < end; i++) {
            result = result.add(A[end][i].multiply(x[i]));
        }
        return result.negate();
    }

    private BigDecimal SumRightS(int start) {
        BigDecimal result = BigDecimal.ZERO;
        for (int i = (start + 1); i < dim; i++) {
            result = result.add(A[start][i].multiply(xNew[i]));
        }
        return result.negate();
    }

    private BigDecimal SumLeftS(int end) {
        BigDecimal result = BigDecimal.ZERO;
        for (int i = 0; i < end; i++) {
            result = result.add(A[end][i].multiply(xNew[i]));
        }
        return result.negate();
    }

    public void GaussMethod() {
        for (int i = 0; i < dim; i++) {
            x[i] = BigDecimal.ZERO;
            int indexOfMainElement = i;
            BigDecimal mainElement = BigDecimal.ZERO;
            for (int j = i; j < dim; j++) {
                if (A[i][j].compareTo(mainElement) > 0.000000000000000001) {
                    mainElement = new BigDecimal(String.valueOf(A[i][j]));
                    indexOfMainElement = j;
                }
            }
            BigDecimal[][] P = MatrixP(i, indexOfMainElement);
            A = MatrixMultiplication(P, A);
            BigDecimal[][] M = MatrixM(i);
            A = MatrixMultiplication(M, A);
            b = VectorMultiplication(M, b);
        }
        x[dim - 1] = b[dim - 1];
        for (int i = (dim - 2); i >= 0; i--) {
            for (int j = (i + 1); j < dim; j++) {
                b[i] = b[i].add(x[j].negate().multiply(A[i][j]));
            }
            x[i] = b[i];
        }
    }

    public void TriDiagonalMethod() {
        BigDecimal[] c = new BigDecimal[dim];
        BigDecimal[] d = new BigDecimal[dim];
        c[0] = A[0][1].divide(A[0][0], precision, RoundingMode.HALF_UP);
        d[0] = b[0].divide(A[0][0], precision, RoundingMode.HALF_UP);
        x[0] = BigDecimal.ZERO;
        for (int i = 1; i < (dim - 1); i++) {
            x[i] = BigDecimal.ZERO;
            BigDecimal divisor = A[i][i].add(A[i][i - 1].negate().multiply(c[i - 1]));
            BigDecimal divider = b[i].add(A[i][i - 1].negate().multiply(d[i - 1]));
            c[i] = A[i][i + 1].divide(divisor, precision, RoundingMode.HALF_UP);
            d[i] = divider.divide(divisor, precision, RoundingMode.HALF_UP);
        }
        x[dim - 1] = BigDecimal.ZERO;
        d[dim - 1] = b[dim - 1].add(A[dim - 1][dim - 2].negate().multiply(d[dim - 2]))
                .divide(A[dim - 1][dim - 1].add(A[dim - 1][dim - 2].negate().multiply(c[dim - 2]))
                        , precision, RoundingMode.HALF_UP);
        x[dim - 1] = d[dim - 1];
        for (int i = (dim - 2); i >= 0; i--) {
            x[i] = d[i].add(c[i].negate().multiply(x[i + 1]));
        }
    }

    public void JacobiMethod() {
        boolean areClose = true;
        System.arraycopy(b, 0, x, 0, dim);
        int iteration = 0;
        while (iteration < 100000) {
            for (int i = 0; i < dim; i++) {
                xNew[i] = (b[i].add(SumLeftJ(i)).add(SumRightJ(i))).divide(A[i][i], precision, RoundingMode.HALF_UP);
            }
            for (int i = 0; i < dim; i++) {
                if (x[i].negate().add(xNew[i]).abs().compareTo(new BigDecimal("1e-10")) > 0) {
                    areClose = false;
                    break;
                } else {
                    areClose = true;
                }
            }
            System.arraycopy(xNew, 0, x, 0, dim);
            if (areClose) {
                System.out.println("Iterations: " + iteration);
                return;
            }
            iteration++;
        }
    }

    public void SeidelMethod() {
        boolean areClose = true;
        System.arraycopy(b, 0, x, 0, dim);
        System.arraycopy(b, 0, xNew, 0, dim);
        int iteration = 0;
        while (iteration < 100000) {
            for (int i = 0; i < dim; i++) {
                xNew[i] = (b[i].add(SumLeftS(i)).add(SumRightS(i))).divide(A[i][i], precision, RoundingMode.HALF_UP);
            }
            for (int i = 0; i < dim; i++) {
                if (x[i].negate().add(xNew[i]).abs().compareTo(new BigDecimal("1e-10")) > 0) {
                    areClose = false;
                    break;
                } else {
                    areClose = true;
                }
            }
            System.arraycopy(xNew, 0, x, 0, dim);
            if (areClose) {
                System.out.println("Iterations: " + iteration);
                return;
            }
            iteration++;
        }
    }

    public void PrintMatrix() {
        System.out.println("A: ");
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                System.out.print(A[i][j] + "\t");
            }
            System.out.println();
        }
        System.out.println("b: ");
        for (int i = 0; i < dim; i++) {
            System.out.println(b[i] + "\t");
        }
        PrintX();
    }

    public void PrintX() {
        System.out.println("expected x: ");
        for (int i = 0; i < dim; i++) {
            System.out.println(expectedX[i] + "\t");
        }
        System.out.println("real x: ");
        for (int i = 0; i < dim; i++) {
            System.out.println(x[i] + "\t");
        }
    }

    public void CheckX() {
        boolean tester = true;
        for (int i = 0; i < dim; i++) {
            if (x[i].negate().add(expectedX[i]).abs().compareTo(new BigDecimal("1e-10")) > 0) {
                tester = false;
                break;
            }
        }
        System.out.println(tester);
    }

    public void CheckAxEqualsTob() {
        boolean tester = true;
        BigDecimal[] Ax = VectorMultiplication(A, x);
        for (int i = 0; i < dim; i++) {
            if (Ax[i].negate().add(b[i]).abs().compareTo(new BigDecimal("1e-7")) > 0) {
                tester = false;
                break;
            }
        }
        System.out.println(tester);
    }

    public static void main(String[] args) {
        Equation test = new Equation();
        test.RandomHilbertMatrix();
        test.PrintMatrix();
        final long start = System.nanoTime();
        test.GaussMethod();
        final long millis = TimeUnit.NANOSECONDS.toMillis(System.nanoTime() - start);
        System.out.println("Task run for: " + millis);
        test.CheckX();
        test.CheckAxEqualsTob();
    }
}
