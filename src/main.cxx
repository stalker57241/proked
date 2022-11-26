#include "config.hxx"
#include "main.hxx"

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		// report version
		std::cout << argv[0] << " Version " << VERSION_MAJOR << "."
						<< VERSION_MINOR << "."
						<< VERSION_PATCH << std::endl;
		std::cout << "Usage: " << argv[0] << " PATH" << std::endl;
		return 1;
	}
	

	return 0;
}
