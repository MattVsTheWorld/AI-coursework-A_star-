#ifndef A_STAR
#define A_STAR

// OPEN // open nodes // to be evaluated
// CLOSED // nodes already evaluated
// add the start node to open
// loop
	// current (temp var) (beginning = starting) = node in OPEN with lowest f()
	// remove current from OPEN
	// add current to CLOSED

// if current is target -> PATH FOUND
	// return

// for each neighjbour of current node (LOOP ALL NEIGHBOURS)
//++
	// if neighbour is CLOSED or BNOT TRAVERSABLE
		// skip to next

// if new path to neighbour is shorter  || OR || neighbour is not open (!OPEN)
	// set f() of NEIGHBOUR
	// set parent of neighbour to current
	// if neighbour not in OPEN list
		// add to OPEN
//--
class A_star {
private:
protected:
public:
};
#endif A_STAR