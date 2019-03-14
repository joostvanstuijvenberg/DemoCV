/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/OpenCV
 *
 * You are free to:
 *    Share � copy and redistribute the material in any medium or format
 *    Adapt � remix, transform, and build upon the material for any purpose, even commercially.
 *
 * The licensor cannot revoke these freedoms as long as you follow the license terms.
 *
 * Under the following terms:
 *    Attribution � You must give appropriate credit, provide a link to the license, and indicate
 *                  if changes were made. You may do so in any reasonable manner, but not in any
 * 	                way that suggests the licensor endorses you or your use.
 *    ShareAlike  � If you remix, transform, or build upon the material, you must distribute your
 *                  contributions under the same license as the original.
 *
 * No additional restrictions � You may not apply legal terms or technological measures that
 * legally restrict others from doing anything the license permits.
 *
 * Notices:
 *    You do not have to comply with the license for elements of the material in the public domain
 *    or where your use is permitted by an applicable exception or limitation. No warranties are
 *    given. The license may not give you all of the permissions necessary for your intended use.
 *    For example, other rights such as publicity, privacy, or moral rights may limit how you use
 *    the material.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "Demo.hpp"

 // Suppress the console window (in Visual Studio).
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#define KEY_ESCAPE				27			// <Esc>
#define KEY_RUN_MANUAL			13			// <Enter>
#define KEY_FLIP_HOR			'!'
#define KEY_FLIP_VER			'@'
#define KEY_WIN_ALTER			'#'
#define KEY_MOVE_LEAVE			'$'
#define KEY_DECREASE_SIZE		'('
#define KEY_INCREASE_SIZE		')'
#define KEY_NORMAL_SIZE			'='

#define WAIT_TIME_INFINITE		0
#define WAIT_TIME_40_MSEC		40

/*
 * ---------------------------------------------------------------------------------------------- *
 * Main()                                                                                         *
 * ---------------------------------------------------------------------------------------------- *
 */
int main(int argc, char** argv)
{
	int key = 0;
	bool run = true;

	// All available demonstrations. Pick one as default.
	BasicMorphologyDemo bmd;
	BitPlaneSlicingDemo bsd;
	BlobDetectionDemo bdd;
	RegionOfInterestDemo rid;
	ColorDemo cld;
	ThresholdDemo thd;
	SmoothingDemo smd;
	EdgeDetectionDemo edd;

	std::map<char, Demo*> demos;
	demos.insert(std::pair<char, Demo*>('A', &bmd));
	demos.insert(std::pair<char, Demo*>('B', &bsd));
	demos.insert(std::pair<char, Demo*>('C', &bdd));
	demos.insert(std::pair<char, Demo*>('D', &rid));
	demos.insert(std::pair<char, Demo*>('E', &cld));
	demos.insert(std::pair<char, Demo*>('F', &thd));
	demos.insert(std::pair<char, Demo*>('G', &smd));
	demos.insert(std::pair<char, Demo*>('H', &edd));
	Demo* d = demos.at('A');

	// All available sources. Pick one as default.
	CameraSource cs0{ 0 }, cs1{ 1 };
	FileSource fs0{ "media/Gears.bmp" }, fs1{ "media/Shapes.bmp" }, fs2{ "media/Colors.jpg" }, fs3{ "media/Things.bmp" };
	MovieSource ms0{ "media/Video.avi" }, ms1{ "media/Video.mp4" };

	std::map<char, Source*> sources;
	sources.insert(std::pair<char, Source*>('a', &cs0));
	sources.insert(std::pair<char, Source*>('b', &cs1));
	sources.insert(std::pair<char, Source*>('c', &fs0));
	sources.insert(std::pair<char, Source*>('d', &fs1));
	sources.insert(std::pair<char, Source*>('e', &fs2));
	sources.insert(std::pair<char, Source*>('f', &fs3));
	sources.insert(std::pair<char, Source*>('g', &ms0));
	sources.insert(std::pair<char, Source*>('h', &ms1));
	Source* s = sources.at('c');

	// All available window placement strategies. Pick one as default.
	WindowStrategy ws0;
	StackedWindowStrategy ws1;
	ShiftedWindowStrategy ws2;
	CircularWindowStrategy ws3;

	std::map<char, WindowStrategy*> windowStrategies;
	windowStrategies.insert(std::pair<char, WindowStrategy*>('0', &ws0));
	windowStrategies.insert(std::pair<char, WindowStrategy*>('1', &ws1));
	windowStrategies.insert(std::pair<char, WindowStrategy*>('2', &ws2));
	windowStrategies.insert(std::pair<char, WindowStrategy*>('3', &ws3));
	WindowStrategy* w = windowStrategies.at('1');

	do {
		// Let the chosen demonstration subclass perform one (1) cycle of its work on the given source,
		// using the given strategy for window placement. The window strategy needs the number of
		// windows and their sizes to calculate the right distribution of windows on the display.
		w->reset(d->getNumberOfWindows(), s->getImage().size());
		d->show();
		d->demonstrate(*s, *w);

		// Wait for a key. In manual mode we will wait forever. In run mode we will wait for 40 msec
		// maximum, thus generating an update rate of approximately 25 fps. This loop will end if <ESC>
		// was pressed.
		key = cv::waitKey(run ? WAIT_TIME_40_MSEC : WAIT_TIME_INFINITE);

		// Capital characters select the demonstration.
		if (demos.count(key) != 0)
		{
			d->hide();
			d = demos.at(key);
			continue;
		}

		// Non-capital characters select the source.
		if (sources.count(key) != 0)
		{
			s = sources.at(key);
			continue;
		}

		// Numeric keys select the window strategy.
		if (windowStrategies.count(key) != 0)
		{
			w = windowStrategies.at(key);
			w->setMoveEnabled(true);
			continue;
		}

		// Other keys influence the behaviour of the demonstration.
		switch (key)
		{
			// Change between manual and continuous mode.
		case KEY_RUN_MANUAL:
			run = !run;
			break;
			// Enable/disable window moving.
		case KEY_MOVE_LEAVE:
			w->setMoveEnabled(!w->isMoveEnabled());
			break;
			// Change the way the window strategy displays windows, if it supports dynamic change.
		case KEY_WIN_ALTER:
			w->alternate();
			break;
			// Flip the image horizontally or vertically.
		case KEY_FLIP_HOR:
			s->toggleFlipHorizontal();
			break;
		case KEY_FLIP_VER:
			s->toggleFlipVertical();
			break;
			// Increase or decrease the image size, or return to normal image size.
		case KEY_INCREASE_SIZE:
			s->increaseSize();
			break;
		case KEY_DECREASE_SIZE:
			s->decreaseSize();
			break;
		case KEY_NORMAL_SIZE:
			s->normalSize();
			break;
		}
	} while (key != KEY_ESCAPE);

	return 0;
}
