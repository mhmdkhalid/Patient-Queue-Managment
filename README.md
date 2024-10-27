# Patient Queue Management App

## Overview

The Patient Queue Management App is a C++ application designed to manage a queue of patients based on their priority levels. It allows healthcare providers to efficiently add, process, update, and display patients in a prioritized manner. The app utilizes a priority queue data structure for managing patient entries, ensuring that those in critical condition are attended to first.

## Features

- **Add Patient**: Add a new patient to the queue with their name, age, and priority level.
- **Display Queue**: View the current list of patients in the queue along with their details.
- **Update Patient**: Update the priority and condition of an existing patient in the queue.
- **Process Patient**: Remove the patient at the front of the queue for treatment.
- **Get Front Patient Name**: Retrieve the name of the patient currently at the front of the queue.
- **Get Queue Size**: Check the number of patients currently in the queue.

## Classes

### `Patient`
- Represents a patient with attributes such as name, age, condition, and priority.
- Methods include constructors, getters, setters, and condition management.

### `PriorityQueue`
- Manages a linked list of patients, ensuring that patients are sorted by priority.
- Methods include insertion, deletion, display, and size retrieval.

### `stackOfVariables`
- Processes lines of code from a file, managing variable declarations and assignments.

## Installation

1. Ensure you have a C++ compiler installed (e.g., g++, clang).
2. Clone or download the repository to your local machine.
3. Navigate to the directory containing the source code.
4. Compile the program using the following command:

   ```bash
   g++ -o patient_queue_management patient_queue_management.cpp
