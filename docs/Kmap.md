Below is a comprehensive documentation of the provided `KMap` class code, which implements a Karnaugh Map (K-Map) solver for simplifying Boolean expressions in a 4x4 grid (4 variables). The documentation includes an overview, class structure, detailed method descriptions, and additional information about usage, assumptions, and limitations. The artifact is formatted as a Markdown document for clarity and portability.



# KMap Class Documentation

## Overview

The `KMap` class is a C++ implementation of a Karnaugh Map solver designed to simplify Boolean expressions for 4-variable functions. A Karnaugh Map is a graphical tool used in digital logic design to minimize Boolean functions by grouping minterms (for Sum of Products, SOP) or maxterms (for Product of Sums, POS). The class supports a 4x4 K-Map grid, handles don't care conditions, and accounts for wrap-around (fringe) and corner groupings to produce a minimal Boolean expression.

### Key Features
- **Map Representation**: A 4x4 grid where cells can be `0` (false for SOP, true for POS), `1` (true for SOP, false for POS), or `2` (don't care).
- **SOP/POS Support**: Configurable for SOP (grouping 1s) or POS (grouping 0s) via the `SOP` variable.
- **Gray Code**: Uses Gray code for row and column labels to ensure adjacent cells differ by one bit.
- **Grouping**: Identifies valid groups (1x1, 1x2, 2x2, etc.), including fringe (wrap-around) and corner cases.
- **Redundancy Elimination**: Removes redundant groupings to ensure minimal implicants.
- **Expression Generation**: Converts groupings into a simplified Boolean expression.
- **File Output**: Saves grouping information to a file (`Map.txt`).

### Assumptions
- The K-Map is fixed at 4x4 (4 variables).
- Input is provided through a partially implemented UI (`inputMap()`), likely part of a Qt-based application (given `QString` and `qDebug` usage).
- The code uses raw pointers and manual memory management.

## Class Structure

### Header Inclusion
```cpp
#include "kmap.h"
```
- Includes the header file `kmap.h`, which likely defines the class structure, data types (e.g., `MTptr`, `FTptr`, `COptr`), and constants (`MROW`, `MCOLUMN`).

### Data Members (Inferred)
- **Grid**:
  - `Map[ROW][COLUMN]`: 4x4 array storing cell values (`0`, `1`, `2`).
- **Dimensions**:
  - `NOV`: Number of variables (fixed at 4).
  - `ROW`, `COLUMN`: Grid dimensions (both 4).
  - `side`: Likely a UI-related parameter (set to 16).
- **Mode**:
  - `SOP`: Boolean mode (1 for SOP, 0 for POS).
- **Gray Code**:
  - `grayX[MCOLUMN]`, `grayY[MROW]`: Arrays storing Gray code strings for columns and rows.
- **Linked Lists**:
  - `MTtop`: Main Table, stores non-fringe groupings.
  - `FTtop`: Fringe Table, stores vertical and horizontal fringe groupings.
  - `FHTtop`: Horizontal Fringe Table, temporary storage for horizontal fringe groupings.
  - `COtop`: Coordinate list, tracks cells in groupings.
- **Pointers**:
  - `MTptr`, `FTptr`, `COptr`, `MTcur`, `FTcur`, `MTprev`, `FTprev`, `MTnext`, `FTnext`: Pointers for traversing linked lists.
- **Flags**:
  - `MapCorner`: Boolean indicating if a corner map (grouping all four corners) exists.

## Methods

### Constructor
```cpp
KMap::KMap()
```
- **Description**: Initializes a 4x4 K-Map for 4 variables.
- **Parameters**: None.
- **Actions**:
  - Sets `NOV = 4`, `ROW = 4`, `COLUMN = 4`, `side = 16`.
  - Sets `SOP = 1` (default SOP mode).
  - Initializes linked list pointers (`MTtop`, `FTtop`, `FHTtop`, `COtop`) to `NULL`.
  - Calls `initGray()` to set up Gray code labels.
- **Return**: None.

### Destructor
```cpp
KMap::~KMap()
```
- **Description**: Cleans up dynamically allocated memory.
- **Parameters**: None.
- **Actions**: Not implemented in the provided code; assumed to deallocate linked lists.
- **Return**: None.

### Gray Code Initialization
```cpp
void KMap::initGray()
```
- **Description**: Initializes Gray code sequences for row and column labels.
- **Parameters**: None.
- **Actions**:
  - Calls `initYGray()` for row labels (`grayY`).
  - Calls `initXGray()` for column labels (`grayX`).
- **Return**: None.

```cpp
void KMap::initYGray()
```
- **Description**: Generates Gray code for rows (e.g., `00`, `01`, `11`, `10` for 4 rows).
- **Parameters**: None.
- **Actions**:
  - Starts with `gray[0] = "0"`, `gray[1] = "1"`.
  - Iteratively builds longer codes by mirroring and appending `0` or `1`.
  - Reverses each code string to match K-Map conventions.
  - Stores results in `grayY`.
- **Return**: None.

```cpp
void KMap::initXGray()
```
- **Description**: Same as `initYGray()` but for columns.
- **Parameters**: None.
- **Actions**: Similar to `initYGray()`, stores results in `grayX`.
- **Return**: None.

### Input Handling
```cpp
void KMap::inputMap()
```
- **Description**: Initializes the K-Map grid and accepts user input (likely via a UI).
- **Parameters**: None.
- **Actions**:
  - Initializes `Map[4][4]` to all `0`s.
  - Contains incomplete UI logic (commented-out) to toggle cell values (`0` → `1` → `2` → `0`) based on user interaction.
  - Calculates UI coordinates (`startX`, `startY`) for rendering the grid.
- **Return**: None.

### Grouping Generation
```cpp
void KMap::MapGenerator()
```
- **Description**: Identifies valid non-fringe groupings of 1s (SOP) or 0s (POS).
- **Parameters**: None.
- **Actions**:
  - Iterates over each cell `(i, j)` in the 4x4 grid.
  - Skips cells not matching the target value (`1` for SOP, `0` for POS).
  - Tries group sizes from 4x4 to 1x1 (halving dimensions).
  - Validates groups:
    - All cells must be target value or don't care (`2`).
    - At least one cell must be the target value (not all don't cares).
  - Calls `redundancyEliminator()` for valid groups.
- **Return**: None.

```cpp
void KMap::FringeMapGenerator_Vertical()
```
- **Description**: Identifies vertical wrap-around groupings (left edge to right edge).
- **Parameters**: None.
- **Actions**:
  - For each row, checks groups spanning columns 0 to `jSize` and columns `COLUMN-1` to `COLUMN-jSize`.
  - Validates both sides of the group.
  - Calls `FringeRedundancyEliminator_Vertical()` for valid groups.
- **Return**: None.

```cpp
void KMap::FringeMapGenerator_Horizontal()
```
- **Description**: Identifies horizontal wrap-around groupings (top edge to bottom edge).
- **Parameters**: None.
- **Actions**:
  - Similar to `FringeMapGenerator_Vertical()` but for rows.
  - Stores groups in `FHTtop`, then merges into `FTtop`.
- **Return**: None.

### Redundancy Elimination
```cpp
void KMap::redundancyEliminator(int i, int j, int iSize, int jSize)
```
- **Description**: Adds a non-fringe group to `MTtop` if it’s not redundant.
- **Parameters**:
  - `i`, `j`: Top-left coordinates of the group.
  - `iSize`, `jSize`: Group dimensions.
- **Actions**:
  - Creates a coordinate list (`COtop`) for the group’s cells.
  - If `MTtop` is empty, adds the group.
  - Otherwise, checks if any cell is not covered by existing groups; adds the group if essential.
- **Return**: None.

```cpp
void KMap::FringeRedundancyEliminator_Vertical(int i1, int j1, int i2, int j2, int iSize, int jSize)
```
- **Description**: Adds a vertical fringe group to `FTtop` if not redundant.
- **Parameters**:
  - `i1`, `j1`: Coordinates of the left-side group.
  - `i2`, `j2`: Coordinates of the right-side group.
  - `iSize`, `jSize`: Group dimensions.
- **Actions**: Similar to `redundancyEliminator()` but for `FTtop`.
- **Return**: None.

```cpp
void KMap::FringeRedundancyEliminator_Horizontal(int i1, int j1, int i2, int j2, int iSize, int jSize)
```
- **Description**: Adds a horizontal fringe group to `FHTtop` if not redundant.
- **Parameters**: Same as `FringeRedundancyEliminator_Vertical()`.
- **Actions**: Similar to `FringeRedundancyEliminator_Vertical()` but for `FHTtop`.
- **Return**: None.

```cpp
void KMap::TheEliminator()
```
- **Description**: Removes `FTtop` entries fully covered by `MTtop` entries.
- **Parameters**: None.
- **Actions**:
  - For each `FTtop` entry, checks if all its cells are covered by `MTtop` or corner map.
  - Deletes covered entries.
- **Return**: None.

```cpp
void KMap::TheEliminatorSecondary()
```
- **Description**: Removes `MTtop` entries covered by larger `FTtop` entries.
- **Parameters**: None.
- **Actions**: Similar to `TheEliminator()` but checks `MTtop` against `FTtop`.
- **Return**: None.

```cpp
void KMap::cleaner()
```
- **Description**: Removes redundant `MTtop` entries covered by other `MTtop` or `FTtop` entries.
- **Parameters**: None.
- **Actions**:
  - For each `MTtop` entry, checks if its cells are covered.
  - Deletes redundant entries.
- **Return**: None.

```cpp
void KMap::cleanerSecondary()
```
- **Description**: Removes redundant `FTtop` entries covered by `MTtop` or other `FTtop` entries.
- **Parameters**: None.
- **Actions**: Similar to `cleaner()` but for `FTtop`.
- **Return**: None.

### Corner Mapping
```cpp
void KMap::cornerMap()
```
- **Description**: Detects and handles a group formed by all four corners.
- **Parameters**: None.
- **Actions**:
  - Checks if corners (0,0), (0,3), (3,0), (3,3) are target value or don't care (not all don't cares).
  - Removes smaller `FTtop` entries covering these corners.
  - Sets `MapCorner = true` if found.
- **Return**: None.

```cpp
void KMap::checkCornerMap()
```
- **Description**: Checks if a corner map exists without modifying `FTtop`.
- **Parameters**: None.
- **Actions**: Similar to `cornerMap()` but only sets `MapCorner`.
- **Return**: None.

### Expression Generation
```cpp
void KMap::ExpressionGen()
```
- **Description**: Prepares for expression generation by reinitializing Gray code.
- **Parameters**: None.
- **Actions**: Calls `initGray()` and optionally `printExp()` (commented out).
- **Return**: None.

```cpp
QString KMap::printExp()
```
- **Description**: Generates the simplified Boolean expression.
- **Parameters**: None.
- **Actions**:
  - Concatenates results from `printMT()`, `printFT()`, and `printCorner()`.
  - Returns a `QString` with the expression.
- **Return**: `QString` containing the expression.

```cpp
QString KMap::printMT()
```
- **Description**: Generates terms for non-fringe groupings (`MTtop`).
- **Parameters**: None.
- **Actions**:
  - For each `MTtop` entry, includes variables with constant Gray code values.
  - SOP: Products (e.g., `AB'`); POS: Sums (e.g., `(A+B')`).
- **Return**: `QString` with terms.

```cpp
QString KMap::printFT()
```
- **Description**: Generates terms for fringe groupings (`FTtop`).
- **Parameters**: None.
- **Actions**: Similar to `printMT()` but handles vertical and horizontal mappings.
- **Return**: `QString` with terms.

```cpp
QString KMap::printCorner()
```
- **Description**: Generates a term for the corner map if `MapCorner = true`.
- **Parameters**: None.
- **Actions**: Includes variables constant across corners.
- **Return**: `QString` with the term.

```cpp
bool KMap::checkChangesY(int index, int start, int end)
```
- **Description**: Checks if a Gray code bit changes across rows.
- **Parameters**:
  - `index`: Bit position in Gray code.
  - `start`, `end`: Row range.
- **Return**: `true` if the bit changes, `false` otherwise.

```cpp
bool KMap::checkChangesX(int index, int start, int end)
```
- **Description**: Same as `checkChangesY()` but for columns.
- **Parameters**: Same as `checkChangesY()`.
- **Return**: `true` if the bit changes, `false` otherwise.

### Output
```cpp
void KMap::outputMap()
```
- **Description**: Saves grouping information to `Map.txt`.
- **Parameters**: None.
- **Actions**:
  - Writes corner map status (`-2` if `MapCorner = true`, `-3` otherwise).
  - Writes `MTtop` entries: `15 i j iSize jSize nextFlag`.
  - Writes `FTtop` entries: `15 i1 j1 i2 j2 iSize jSize nextFlag`.
- **Return**: None.

### Utility Methods
```cpp
void KMap::setSOP(int i)
```
- **Description**: Sets the K-Map mode.
- **Parameters**:
  - `i`: `1` for SOP, `0` for POS.
- **Return**: None.

```cpp
int KMap::GenerateBoxNO(int XCo, int YCo)
```
- **Description**: Converts Gray code coordinates to a minterm number.
- **Parameters**:
  - `XCo`, `YCo`: Column and row indices.
- **Return**: Integer minterm number.

```cpp
void KMap::set(int NOV, int ROW, int COLUMN, int side)
```
- **Description**: Configures K-Map parameters.
- **Parameters**:
  - `NOV`, `ROW`, `COLUMN`, `side`: New values.
- **Actions**:
  - Updates class members.
  - Reinitializes pointers and Gray code.
- **Return**: None.

```cpp
void KMap::TheMapIs()
```
- **Description**: Iterates over the map (incomplete implementation).
- **Parameters**: None.
- **Actions**: Loops through `Map` but lacks functionality.
- **Return**: None.

## Usage Example
1. **Initialize**:
   ```cpp
   KMap kmap;
   kmap.setSOP(1); // SOP mode
   ```
2. **Input Map** (manually for simplicity):
   ```cpp
   kmap.Map[0][0] = 1; kmap.Map[0][3] = 1;
   kmap.Map[3][0] = 1; kmap.Map[3][3] = 1;
   ```
3. **Generate Groups**:
   ```cpp
   kmap.MapGenerator();
   kmap.FringeMapGenerator_Vertical();
   kmap.FringeMapGenerator_Horizontal();
   kmap.cornerMap();
   ```
4. **Eliminate Redundancies**:
   ```cpp
   kmap.TheEliminator();
   kmap.TheEliminatorSecondary();
   kmap.cleaner();
   kmap.cleanerSecondary();
   ```
5. **Generate Expression**:
   ```cpp
   QString expr = kmap.printExp();
   cout << expr.toStdString() << endl; // Outputs: "The expression is: A'B' + AB"
   ```
6. **Save Output**:
   ```cpp
   kmap.outputMap(); // Writes to Map.txt
   ```

## Limitations
- **Fixed Size**: Hardcoded for 4x4 K-Maps; not easily extensible to other sizes.
- **Incomplete UI**: `inputMap()` suggests a Qt-based UI but is incomplete.
- **Complexity**: Multiple redundancy elimination passes could be optimized.
- **Memory Management**: Uses raw pointers; modern C++ (e.g., smart pointers) would improve safety.
- **Error Handling**: Limited validation for inputs or edge cases.

## Dependencies
- **Standard Libraries**: `iostream`, `fstream`, `string`, `cmath`.
- **Qt**: `QString`, `qDebug` indicate Qt dependency for UI and debugging.
- **Custom Header**: `kmap.h` for class definitions and types.

## File Output Format
- **Map.txt**:
  - Line 1: `-2` (corner map exists) or `-3` (no corner map).
  - `MTtop` entries: `15 i j iSize jSize nextFlag` (`-1` for last).
  - `FTtop` entries: `15 i1 j1 i2 j2 iSize jSize nextFlag` (`-1` for last).
