template <typename T>
class Tracker : T
{
public:
  static int counter;
};

// Initialize the static member outside of the class definition
template <typename T>
int Tracker<T>::counter = 0;
