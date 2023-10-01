# Word-Freq-Analyzer
Experience lightning-fast performance with this high-speed Text Analytics Toolkit in C, powered by custom Binary Search Trees. Despite dynamic word storage, the algorithm achieves an impressive O(n) time complexity, where 'n' corresponds to the total number of words processed.

**Description:**
The Word Frequency Analyzer is a personal project I developed as part of my Data Structures and Algorithms course. In the rapidly growing field of data analytics, text analytics plays a pivotal role. This project focuses on extracting a key text analytics metric: the frequency of occurrence of the most common words in a text document.

To achieve this, I designed a program that can process text documents sourced from Project Gutenberg, a renowned initiative that digitizes out-of-copyright books and makes them freely accessible. These documents include literary classics like "Moby Dick" and are provided in a simple, resilient ASCII text format.

The project involves several essential steps:

**1. Preprocessing:** Text analysis requires some preprocessing steps:
   - Tokenization and normalization: Identifying individual words and converting them to lowercase.
   - Stopword removal: Eliminating common words that don't contribute significantly to document semantics.
   - Stemming: Reducing words to their root form to remove variations.

**2. Implementation of the Dictionary ADT:** I created a binary search tree-based Dictionary ADT to store words and their occurrence counts efficiently.

**3. Efficient Computation:** The program is designed for efficiency, with the ability to process large data files in under a second.

**4. Error Handling:** Robust error handling ensures that the program gracefully handles various error scenarios, such as incorrect command-line arguments or unreadable files.

**5. Testing and Debugging:** Thorough testing using provided data files and custom test cases, along with debugging techniques, ensures the program's correctness and reliability.

**6. GitHub Repository:** You can find the complete source code and documentation for this project in my GitHub repository.

This project showcases my skills in data structures, algorithms, and software development, highlighting my ability to work with real-world data and create efficient and error-tolerant solutions. It's a testament to my dedication to mastering key concepts in computer science and applying them to practical challenges.

**Running the Program and Testing:**

To utilize this Text Analytics Toolkit and test it with your own input, follow these simple steps:

1. **Clone the Repository:**
   - Clone this GitHub repository to your local machine using the following command:
     ```
     git clone https://github.com/yourusername/top-words-extractor.git
     ```
   - Replace "yourusername" with your actual GitHub username.

2. **Compile the Program:**
   - Navigate to the project directory:
     ```
     cd top-words-extractor
     ```
   - Compile the program using the provided Makefile:
     ```
     make
     ```

3. **Run the Program:**
   - Execute the program by specifying the number of top words you want to extract (default is 10) and the input text file. For example:
     ```
     ./tw 20 data/your_input_file.txt
     ```
     - Replace "your_input_file.txt" with the name of your input text file.
     - You can adjust the number of top words as needed.

4. **Review the Results:**
   - The program will display the top words along with their frequencies, sorted in descending order of frequency.

5. **Test with Custom Input:**
   - If you'd like to test the program with different input files, place your text files in the "data" directory.
   - Run the program as described in step 3, specifying your custom input file.

Feel free to experiment with various input files to analyze the word frequencies. The program's efficiency and accuracy make it a valuable tool for text analysis tasks.
