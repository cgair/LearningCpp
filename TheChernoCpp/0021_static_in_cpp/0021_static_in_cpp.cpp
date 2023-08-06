/**
 * @file 0021_static_in_cpp.cpp
 * @author chenge
 * @brief C++类和结构体外的 static
 * @version 0.1
 * @date 2023-08-05
 * 
 * @copyright Copyright (c) 2023
 * 
 * **Key Takeaway**
 * 1. When used outside of a class or struct, the static keyword means that 
 *    the symbol (variable or function) declared as static will have internal linkage. 
 * 
 * 2. Try to mark your functions and variables static unless you need them to be linked
 *    across translate unit.
 */

int val = 12;

static int s_variable = 13; // What does it actually means
                            // that this variable is only 
                            // to be linked internally in this translate unit?

static void foo() { }

// ❗️ the linker is not going to look outside of the scope of this translate unit 
//  for that symbol definition.