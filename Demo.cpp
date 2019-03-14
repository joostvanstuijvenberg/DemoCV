/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "Demo.h"

/*
 * ---------------------------------------------------------------------------------------------- *
 * Demo::show()                                                                                   *
 * ---------------------------------------------------------------------------------------------- *
 */
void Demo::show() const
{
	// Make namedWindow-instances for all windows, as requested by the subclass. Note that this has
	// to be done *after* the default constructor for Demo has been called, so it's not an option
	// to put this in the superclass constructor.
	for (const auto& name : windows)
		cv::namedWindow(name, CV_WINDOW_AUTOSIZE);
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * Demo::hide()                                                                                   *
 * ---------------------------------------------------------------------------------------------- *
 */
void Demo::hide() const
{
	// Destroy all windows that belong to this demonstration (and this demonstration only!).
	for (const auto& name : windows)
		cv::destroyWindow(name);
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * Demo::getNumberOfWindows()                                                                     *
 * ---------------------------------------------------------------------------------------------- *
 */
int Demo::getNumberOfWindows() const
{
	return (int)this->windows.size();
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * Demo::demonstrate()                                                                            *
 * ---------------------------------------------------------------------------------------------- *
 */
void Demo::demonstrate(Source& source, WindowStrategy& windowStrategy) {
	original = source.getImage();
	assert(!original.empty());
}