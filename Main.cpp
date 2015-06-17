// CIS22B
// LAB6
// Cameron March
// Main.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

// Node for linked list
struct node {

	// Node's name
	std::string name;

	// Amount customer owes
	double amount;

	// Next node in the list
	node* next;
};

// Custom linked list
class LinkedList
{
public:

	// Constructor without head
	LinkedList()
	{
		size_ = 0;
	}

	// Constructor with head
	LinkedList(node* head)
	{
		// Set head to first entry and make next itself
		head_ = head;
		head_->next = head_;

		size_ = 1;
	}

	// Append an entry to the end of the list
	void append(node* entry)
	{
		// Exception handling
		try{
			// If amount owed is negative, throw exception
			if(entry->amount < 0)
			{
				throw -1;
			}

			// If this list doesn't have a head
			if(size_ == 0)
			{
				// Assign first entry as head and assign
				// next to point to itself
				head_ = entry;
				head_->next = head_;

				// Increase size
				size_++;
			}
			else
			{
				// Start at head of list
				node* last = head_;

				// Iterate through list until the last node
				for(int i = 1; i < size_; i++)
				{
					last = last->next;
				}

				// Change the last node to point at new node,
				// and make the new node point at head
				entry->next = head_;
				last->next = entry;

				// Increase size
				size_++;
			}
		}
		// Catch exceptions
		catch(int e)
		{
			// Amount Owed Negative Exception
			if(e == -1)
			{	
				// Error message
				std::cout << "Error: " << entry->name << std::endl;
				std::cout << "\tCannot have customers with negative amount owed\n" << std::endl;
			}
		}
	}

	// Remove a node by customer name
	void remove(std::string name)
	{
		// If there are no elements in the list
		if(size_ == 0)
		{
			// Error message
			std::cout << "Cannot remove, list is empty" << std::endl;
		}
		else
		{
			// Start searching from the second node so we can easily
			// track the previous node by starting at head
			node* previous = head_;
			node* current = head_->next;

			// Iterate through the list
			for(int i = 0; i < size_; i++)
			{
				// Compare names of nodes with the name
				// we want to remove
				if(name.compare(current->name) == 0)
				{
					// If we are going to remove the head, we
					// have to assign a new head for the list
					if(current == head_)
					{
						head_ = current->next;
					}

					// Have the previous node skip over the one
					// we want to remove
					previous->next = current->next;

					// Free memory
					delete current;

					// To escape the loop
					i = size_;

					// Reduce size
					size_--;

					std::cout << name << " removed... " << std::endl;
				}

				// If we didnt find the node to remove, move to the next one
				current = current->next;
				previous = previous->next;
			}
		}
	}

	// Save the current state of the list in a text document
	void save(std::string filepath)
	{
		// Open file
		std::ofstream outFile(filepath.c_str());

		// Start at the head
		node* current = head_;

		std::cout << "Saving list to " << filepath << std::endl;

		// Iterate through the list
		for(int i = 0; i < size_; i++)
		{
			// Save node in the same format we loaded it
			outFile << current->name << " " << current->amount << std::endl;

			// Move to the next node
			current = current->next;
		}

		// Close the file stream
		outFile.close();
	}

	// Prints the list
	void print()
	{
		// Start at the head
		node* current = head_;

		std::cout << "Printing list... " << std::endl;

		// Iterate through each node
		for(int i = 0; i < size_; i++)
		{

			// Print node information
			std::cout << "Node " << (i + 1) << ": " << std::endl;
			std::cout << "\tName: " << current->name << std::endl;
			std::cout << "\tAmount Owed: $" << current->amount << "\n" << std::endl;

			// Go to the next node
			current = current->next;
		}
	}

	// Prints nodes that owe above the given amount of money
	void printAboveThreshold(double amount)
	{
		// Start at the head
		node* current = head_;

		std::cout << "Printing customers who owe more than $" << amount << ":" << std::endl;

		// Iterate through the list's nodes
		for(int i = 0; i < size_; i++)
		{
			// If the nodes amount is greater than the given amount...
			if(current->amount >= amount)
			{
				// ...print the nodes name
				std::cout << "\t" << current->name << std::endl;
			}

			// Go to the next node
			current = current->next;
		}

		std::cout << std::endl;
	}

	// Returns the size of the list
	int size()
	{
		return size_;
	}

private:
	// First node in the list
	node* head_;

	// Size of the list
	int size_;
};

int main()
{
	// Open file
	std::ifstream inFile("customerFile.txt");
	std::string input;
	node* entry;

	// Create the list
	LinkedList* list = new LinkedList();

	// Iterate through each line
	while(inFile >> input)
	{
		// Create new node
		entry = new node;

		// Add name to node
		entry->name = input;

		// Add amount owed to node
		inFile >> input;
		entry->amount = atof(input.c_str());

		// Append node to the list
		list->append(entry);
	}

	// Close input file
	inFile.close();

	// Print full list
	list->print();

	// Print list with customers owing more than $50
	list->printAboveThreshold(50);

	// Remove Customer1
	list->remove("Customer1");

	// Print the smaller list
	list->print();

	// Save list to output.txt
	list->save("output.txt");

	return 0;
}
