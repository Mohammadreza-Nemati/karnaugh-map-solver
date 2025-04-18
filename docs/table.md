Below is a comprehensive documentation of the `Table` class provided in the code, which serves as a utility class for managing data structures used in the `KMap` class (previously documented). The `Table` class handles the creation, insertion, and deletion of entries in linked lists for map table entries (`MapTable`), fringe map table entries (`FringeMapTable`), and coordinate lists (`coOrdinates`). This documentation complements the `KMap` class documentation and is formatted as a Markdown document for clarity.



# Table Class Documentation

## Overview

The `Table` class is a C++ utility class designed to manage linked list data structures used in a Karnaugh Map (K-Map) solver, as implemented in the `KMap` class. It provides methods to create, insert, and delete entries for three primary data structures:
- **MapTable**: Stores non-fringe K-Map groupings (position and size).
- **FringeMapTable**: Stores fringe (wrap-around) K-Map groupings (positions for both sides and size).
- **coOrdinates**: Stores cell coordinates with a status flag for tracking coverage in redundancy checks.

The class uses a stack-based (LIFO) approach for inserting entries and includes methods for memory management of these linked lists. It is tightly coupled with the `KMap` class, providing the backbone for storing and manipulating K-Map groupings.

### Key Features
- **Dynamic Memory Allocation**: Creates nodes for `MapTable`, `FringeMapTable`, and `coOrdinates` using `new`.
- **Linked List Management**: Supports stack-based insertion (`push`) and deletion of lists.
- **Data Structures**:
  - `MapTable` for standard K-Map groups.
  - `FringeMapTable` for wrap-around groups.
  - `coOrdinates` for tracking individual cells.
- **Memory Cleanup**: Provides a method to deallocate coordinate lists.

### Assumptions
- The class is used within the context of a 4x4 K-Map solver (as defined in `KMap`).
- It relies on raw pointers for memory management, typical of older C++ code.
- The header file `table.h` defines the class structure and data types.
- The class does not handle errors (e.g., memory allocation failures).

## Class Structure

### Header Inclusion
```cpp
#include "table.h"
```
- Includes `table.h`, which defines the `Table` class, its data structures (`MapTable`, `FringeMapTable`, `coOrdinates`), and member pointers.

### Data Members (Inferred)
The following are inferred from the method implementations and their usage in `KMap`:
- **MapTable Structure**:
  - `i`, `j`: Top-left coordinates of a non-fringe group.
  - `iSize`, `jSize`: Dimensions of the group (e.g., 2x2).
  - `next`: Pointer to the next `MapTable` node.
- **FringeMapTable Structure**:
  - `i1`, `j1`: Coordinates of the first side of a fringe group.
  - `i2`, `j2`: Coordinates of the second side (e.g., opposite edge).
  - `iSize`, `jSize`: Dimensions of the group.
  - `next`: Pointer to the next `FringeMapTable` node.
- **coOrdinates Structure**:
  - `i`, `j`: Row and column indices of a cell.
  - `status`: Boolean flag indicating if the cell is covered (used in redundancy checks).
  - `next`: Pointer to the next `coOrdinates` node.
- **Pointers**:
  - `MTtop`: Head of the `MapTable` linked list.
  - `FTtop`: Head of the `FringeMapTable` linked list (vertical and horizontal fringe).
  - `FHTtop`: Head of the `FringeMapTable` linked list for horizontal fringe groups.
  - `COtop`: Head of the primary `coOrdinates` linked list.
  - `COtop2`: Head of a secondary `coOrdinates` linked list (possibly for temporary use).
  - `MTptr`, `FTptr`, `COptr`, `COptr2`: Temporary pointers for traversal and manipulation.

## Methods

### MapTable Methods

#### CreateEntry (MapTable)
```cpp
Table::MapTable *Table::CreateEntry(int i, int j, int iSize, int jSize)
```
- **Description**: Creates a new `MapTable` node for a non-fringe K-Map group.
- **Parameters**:
  - `i`, `j`: Top-left coordinates of the group.
  - `iSize`, `jSize`: Dimensions of the group (e.g., 1x2, 2x2).
- **Actions**:
  - Allocates a new `MapTable` node using `new`.
  - Initializes `i`, `j`, `iSize`, `jSize`.
  - Sets `next` to `NULL`.
- **Return**: Pointer to the new `MapTable` node.
- **Usage**: Called by `KMap::redundancyEliminator()` to create entries for non-fringe groups.

#### pushEntry (MapTable)
```cpp
void Table::pushEntry(Table::MapTable *np)
```
- **Description**: Inserts a `MapTable` node at the head of the `MTtop` linked list (stack-based).
- **Parameters**:
  - `np`: Pointer to the `MapTable` node to insert.
- **Actions**:
  - If `MTtop` is `NULL`, sets `MTtop` to `np`.
  - Otherwise, updates `np->next` to point to the current `MTtop` and sets `MTtop` to `np`.
- **Return**: None.
- **Usage**: Called by `KMap::redundancyEliminator()` to add non-fringe groups to `MTtop`.

### FringeMapTable Methods

#### CreateEntry (FringeMapTable)
```cpp
Table::FringeMapTable *Table::CreateEntry(int i1, int j1, int i2, int j2, int iSize, int jSize)
```
- **Description**: Creates a new `FringeMapTable` node for a fringe (wrap-around) K-Map group.
- **Parameters**:
  - `i1`, `j1`: Coordinates of the first side of the group.
  - `i2`, `j2`: Coordinates of the second side (e.g., opposite edge).
  - `iSize`, `jSize`: Dimensions of the group.
- **Actions**:
  - Allocates a new `FringeMapTable` node using `new`.
  - Initializes `i1`, `j1`, `i2`, `j2`, `iSize`, `jSize`.
  - Sets `next` to `NULL`.
- **Return**: Pointer to the new `FringeMapTable` node.
- **Usage**: Called by `KMap::FringeRedundancyEliminator_Vertical()` and `KMap::FringeRedundancyEliminator_Horizontal()`.

#### pushEntry (FringeMapTable)
```cpp
void Table::pushEntry(Table::FringeMapTable *np)
```
- **Description**: Inserts a `FringeMapTable` node at the head of the `FTtop` linked list.
- **Parameters**:
  - `np`: Pointer to the `FringeMapTable` node to insert.
- **Actions**:
  - If `FTtop` is `NULL`, sets `FTtop` to `np`.
  - Otherwise, updates `np->next` to point to the current `FTtop` and sets `FTtop` to `np`.
- **Return**: None.
- **Usage**: Called by `KMap::FringeRedundancyEliminator_Vertical()` to add vertical fringe groups.

#### pushHEntry (FringeMapTable)
```cpp
void Table::pushHEntry(Table::FringeMapTable *np)
```
- **Description**: Inserts a `FringeMapTable` node at the head of the `FHTtop` linked list (for horizontal fringe groups).
- **Parameters**:
  - `np`: Pointer to the `FringeMapTable` node to insert.
- **Actions**:
  - If `FHTtop` is `NULL`, sets `FHTtop` to `np`.
  - Otherwise, updates `np->next` to point to the current `FHTtop` and sets `FHTtop` to `np`.
- **Return**: None.
- **Usage**: Called by `KMap::FringeRedundancyEliminator_Horizontal()` to add horizontal fringe groups.

### coOrdinates Methods

#### emergeCoOrdinate
```cpp
Table::coOrdinates *Table::emergeCoOrdinate(int i, int j, bool status)
```
- **Description**: Creates a new `coOrdinates` node for a K-Map cell.
- **Parameters**:
  - `i`, `j`: Row and column indices of the cell.
  - `status`: Boolean flag (typically `false` initially) for redundancy checks.
- **Actions**:
  - Allocates a new `coOrdinates` node using `new`.
  - Initializes `i`, `j`, `status`.
  - Sets `next` to `NULL`.
- **Return**: Pointer to the new `coOrdinates` node.
- **Usage**: Called by `KMap` methods (e.g., `redundancyEliminator()`) to track group cells.

#### insertCoOrdinate
```cpp
void Table::insertCoOrdinate(Table::coOrdinates *np)
```
- **Description**: Inserts a `coOrdinates` node at the head of the `COtop` linked list.
- **Parameters**:
  - `np`: Pointer to the `coOrdinates` node to insert.
- **Actions**:
  - If `COtop` is `NULL`, sets `COtop` to `np`.
  - Otherwise, updates `np->next` to point to the current `COtop` and sets `COtop` to `np`.
- **Return**: None.
- **Usage**: Called by `KMap` to build coordinate lists for groups.

#### emergeCoOrdinate2
```cpp
Table::coOrdinates *Table::emergeCoOrdinate2(int i, int j, bool status)
```
- **Description**: Creates a new `coOrdinates` node for the secondary coordinate list (`COtop2`).
- **Parameters**:
  - `i`, `j`: Row and column indices.
  - `status`: Boolean flag.
- **Actions**: Identical to `emergeCoOrdinate()` but uses `COptr2` for the secondary list.
- **Return**: Pointer to the new `coOrdinates` node.
- **Usage**: Not explicitly used in the provided `KMap` code; possibly for temporary or alternative coordinate tracking.

#### insertCoOrdinate2
```cpp
void Table::insertCoOrdinate2(Table::coOrdinates *np)
```
- **Description**: Inserts a `coOrdinates` node at the head of the `COtop2` linked list.
- **Parameters**:
  - `np`: Pointer to the `coOrdinates` node to insert.
- **Actions**: Identical to `insertCoOrdinate()` but for `COtop2`.
- **Return**: None.
- **Usage**: Not used in the provided `KMap` code; likely for future or alternative functionality.

#### deleteCoOrdinateList
```cpp
void Table::deleteCoOrdinateList(Table::coOrdinates *top)
```
- **Description**: Deallocates all nodes in a `coOrdinates` linked list.
- **Parameters**:
  - `top`: Head of the `coOrdinates` list to delete.
- **Actions**:
  - Traverses the list, deleting each node using `delete`.
  - Uses `save` to store the next pointer before deletion.
- **Return**: None.
- **Usage**: Called by `KMap::TheEliminator()` to clean up coordinate lists after redundancy checks.

## Usage Example
The `Table` class is used by the `KMap` class to manage groupings. Below is an example within the `KMap` context:

```cpp
// Creating and inserting a non-fringe group
Table table;
Table::MapTable *entry = table.CreateEntry(0, 0, 2, 2); // 2x2 group at (0,0)
table.pushEntry(entry); // Add to MTtop

// Creating and inserting coordinates for a group
Table::coOrdinates *coord = table.emergeCoOrdinate(0, 0, false); // Cell (0,0)
table.insertCoOrdinate(coord); // Add to COtop

// Creating and inserting a fringe group
Table::FringeMapTable *fringeEntry = table.CreateEntry(0, 0, 0, 3, 2, 1); // Vertical fringe
table.pushEntry(fringeEntry); // Add to FTtop

// Cleaning up a coordinate list
table.deleteCoOrdinateList(table.COtop); // Deallocate COtop list
```

## Integration with KMap
- **MapTable**: Used in `KMap::redundancyEliminator()` to store non-fringe groups (`MTtop`).
- **FringeMapTable**: Used in `KMap::FringeRedundancyEliminator_Vertical()` (`FTtop`) and `KMap::FringeRedundancyEliminator_Horizontal()` (`FHTtop`).
- **coOrdinates**: Used across `KMap` methods (e.g., `TheEliminator()`, `cleaner()`) to track cells for redundancy checks.
- **Memory Management**: `deleteCoOrdinateList()` ensures no memory leaks when coordinate lists are no longer needed.

## Limitations
- **Raw Pointers**: Uses manual memory management, which is error-prone; modern C++ smart pointers (e.g., `std::unique_ptr`) would improve safety.
- **No Error Handling**: Does not check for memory allocation failures or invalid inputs.
- **Secondary Coordinate List**: `emergeCoOrdinate2()` and `insertCoOrdinate2()` are unused in the provided `KMap` code, suggesting incomplete or planned functionality.
- **No Deletion for MapTable/FringeMapTable**: Lacks methods to delete entire `MapTable` or `FringeMapTable` lists (though `KMap` handles individual node deletion).

## Dependencies
- **Standard Library**: `new` and `delete` operators (implying `<new>` or standard library).
- **Custom Header**: `table.h` defines `MapTable`, `FringeMapTable`, `coOrdinates`, and class members.
