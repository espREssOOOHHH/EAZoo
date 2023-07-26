# EA ZOO -- a demo for Quantum Evolutionary Algorithm(QEA) and Genetic Algorithm(GA)

## Introduction to Evolutionary Algorithms
Evolutionary algorithms (EAs) are optimization methods that mimic natural evolution to find high-quality solutions for 
complex problems. EAs work with a population of solutions, encoded as strings of symbols, and apply stochastic operators
to modify and improve them based on a fitness function. EAs can explore the search space and avoid local optima by using
the diversity and adaptability of the population.

This demo implements two types of EAs: genetic algorithms (GAs) and quantum evolutionary algorithms (QEAs). 
GAs use binary strings and operators such as crossover and mutation to generate new solutions. 
QEAs use quantum bits (qubits) and operators based on quantum mechanics, such as quantum superposition 
and quantum interference, to manipulate the solutions.

### Genetic Algorithms

Genetic algorithms (GAs) are based on an analogy with genetic structure and behavior of chromosomes in natural populations.
A GA maintains a population of binary strings, each representing a potential solution to the problem. 
A GA starts with an initial population of randomly generated strings, and then iterates the following steps until 
a termination criterion is met:

- **Evaluation**: The fitness function is applied to each string in the population to measure its quality as a solution.
- **Selection**: The fitter strings are chosen to form a mating pool, using probabilistic methods such as roulette wheel selection or tournament selection.
- **Crossover**: Pairs of strings from the mating pool are recombined to produce new strings, by exchanging segments of their bits at random points.
- **Mutation**: Each bit in the new strings has a small probability of being flipped, to introduce some variation and diversity in the population.

The new strings replace the old ones in the population, forming a new generation. 
The GA repeats this process until a satisfactory solution is found or a maximum number of generations is reached.

GAs have several advantages over traditional optimization methods. First, GAs are robust and flexible, 
as they can handle noisy, nonlinear, multimodal, and high-dimensional problems 
without requiring much prior knowledge or assumptions about the problem structure. 
Second, GAs are parallel and scalable, as they can exploit the information from multiple 
solutions simultaneously and adapt to changing environments. Third, GAs are easy to implement 
and modify, as they only require a suitable encoding scheme and a fitness function for the problem.

However, GAs also have some limitations and challenges. First, GAs may suffer from premature convergence, 
where the population loses diversity and gets stuck at a suboptimal solution. This can be caused by various 
factors, such as inappropriate parameter settings, insufficient exploration, or deceptive fitness landscapes. 
Second, GAs may have difficulty in finding optimal or near-optimal solutions for some problems that require 
high precision or have complex constraints. This can be due to the limitations of binary encoding, crossover 
operator, or fitness function. Third, GAs may be computationally expensive or inefficient for some problems 
that have large search spaces or require many evaluations. This can be alleviated by using parallel or distributed 
computing techniques or hybridizing GAs with other methods.

### Quantum Evolutionary Algorithms

Quantum evolutionary algorithms (QEAs) are inspired by both quantum computing and evolutionary computing. 
A QEA maintains a population of qubits, each representing a superposition of two states: 0 and 1. 
A qubit can be described by a unit vector in a two-dimensional complex Hilbert space:

$$
|\psi\rangle = \alpha|0\rangle + \beta|1\rangle
$$

where $\alpha$ and $\beta$ are complex coefficients such that $|\alpha|^2 + |\beta|^2 = 1$. 
The coefficients $\alpha$ and $\beta$ determine the probability amplitudes of observing 0 or 1 
when measuring the qubit:

$$
P(0) = |\alpha|^2 \quad P(1) = |\beta|^2
$$

A QEA starts with an initial population of qubits with equal probability amplitudes 
($\alpha = \beta = \frac{1}{\sqrt{2}}$), and then iterates the following steps until a termination criterion is met:

- **Evaluation**: The fitness function is applied to each qubit in the population, by measuring its state and obtaining either 0 or 1. The measurement collapses the qubit to the observed state, and the fitness value is assigned to that state.
- **Selection**: The fitter states are chosen to form a mating pool, using probabilistic methods similar to GAs.
- **Crossover**: Pairs of qubits from the mating pool are recombined to produce new qubits, by applying quantum gates such as controlled-NOT or swap gates to manipulate their coefficients.
- **Mutation**: Each coefficient in the new qubits has a small probability of being rotated, to introduce some variation and diversity in the population.

The new qubits replace the old ones in the population, forming a new generation. 
The QEA repeats this process until a satisfactory solution is found or a maximum number 
of generations is reached.

QEAs have several advantages over GAs and other classical EAs. First, QEAs have a higher 
representation power, as they can encode multiple states in a single qubit using quantum superposition. 
This allows QEAs to explore a larger and richer search space than GAs. Second, QEAs have a faster convergence 
speed, as they can exploit quantum interference to enhance the probability amplitudes of fitter states and 
reduce those of unfit states. This allows QEAs to amplify the difference between good and bad solutions and 
accelerate the search process. Third, QEAs have a better diversity preservation, as they can avoid premature 
convergence by using quantum uncertainty and measurement. This allows QEAs to maintain a balance between 
exploration and exploitation and escape from local optima.

However, QEAs also have some limitations and challenges. First, QEAs may suffer from measurement errors, 
where the observed state of a qubit does not match its true state due to noise or decoherence. This can 
cause QEAs to lose information and degrade the quality of solutions. Second, QEAs may have difficulty in 
designing suitable quantum operators, such as quantum gates or rotation angles, for different problems. 
This can affect the performance and efficiency of QEAs. Third, QEAs may be computationally complex or impractical 
for some problems that require large populations or high-dimensional spaces. This can be overcome by using 
quantum computing hardware or simulating QEAs on classical computers.

## Usage

You can use these two algorithms mainly like main.cpp shows. Remember that **QuantumGeneticAlgorithm** depends on 
**Eigen 3**, where **GeneticAlgorithm** does not.
