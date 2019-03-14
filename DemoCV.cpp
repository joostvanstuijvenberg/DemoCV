/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 *
 * You are free to:
 *    Share - copy and redistribute the material in any medium or format
 *    Adapt - remix, transform, and build upon the material for any purpose, even commercially.
 *
 * The licensor cannot revoke these freedoms as long as you follow the license terms.
 *
 * Under the following terms:
 *    Attribution - You must give appropriate credit, provide a link to the license, and indicate
 *                  if changes were made. You may do so in any reasonable manner, but not in any
 * 	                way that suggests the licensor endorses you or your use.
 *    ShareAlike  - If you remix, transform, or build upon the material, you must distribute your
 *                  contributions under the same license as the original.
 *
 * No additional restrictions - You may not apply legal terms or technological measures that
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

#include <memory>

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
#define WAIT_TIME_25_FPS		40          // approx. 40 msec per frame => 25 fps

using namespace std;

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
    std::map<char, shared_ptr<Demo>> demos;
    demos.insert(pair<char, shared_ptr<Demo>>('A', make_shared<BasicMorphologyDemo>()));
    demos.insert(pair<char, shared_ptr<Demo>>('B', make_shared<BitPlaneSlicingDemo>()));
    demos.insert(pair<char, shared_ptr<Demo>>('C', make_shared<BlobDetectionDemo>()));
    demos.insert(pair<char, shared_ptr<Demo>>('D', make_shared<RegionOfInterestDemo>()));
    demos.insert(pair<char, shared_ptr<Demo>>('E', make_shared<ColorDemo>()));
    demos.insert(pair<char, shared_ptr<Demo>>('F', make_shared<ThresholdDemo>()));
    demos.insert(pair<char, shared_ptr<Demo>>('G', make_shared<SmoothingDemo>()));
    demos.insert(pair<char, shared_ptr<Demo>>('H', make_shared<EdgeDetectionDemo>()));
    auto d = demos.at('A');

    // All available sources. Pick one as default.
    std::map<char, shared_ptr<Source>> sources;
    sources.emplace(pair<char, shared_ptr<CameraSource>>('a', make_shared<CameraSource>(0)));
    sources.emplace(pair<char, shared_ptr<CameraSource>>('b', make_shared<CameraSource>(1)));
    sources.emplace(pair<char, shared_ptr<ImageSource>>('c', make_shared<ImageSource>("media/Gears.bmp")));
    sources.emplace(pair<char, shared_ptr<ImageSource>>('d', make_shared<ImageSource>("media/Shapes.bmp")));
    sources.emplace(pair<char, shared_ptr<ImageSource>>('e', make_shared<ImageSource>("media/Colors.jpg")));
    sources.emplace(pair<char, shared_ptr<ImageSource>>('f', make_shared<ImageSource>("media/Things.bmp")));
    sources.emplace(pair<char, shared_ptr<MovieSource>>('g', make_shared<MovieSource>("media/Video.avi")));
    sources.emplace(pair<char, shared_ptr<MovieSource>>('h', make_shared<MovieSource>("media/Video.mp4")));
    auto s = sources.at('c');

    // All available window placement strategies. Pick one as default.
    std::map<char, shared_ptr<WindowStrategy>> windowStrategies;
    windowStrategies.emplace(pair<char, shared_ptr<WindowStrategy>>('0', make_shared<WindowStrategy>()));
    windowStrategies.emplace(pair<char, shared_ptr<WindowStrategy>>('1', make_shared<StackedWindowStrategy>()));
    windowStrategies.emplace(pair<char, shared_ptr<WindowStrategy>>('2', make_shared<ShiftedWindowStrategy>()));
    windowStrategies.emplace(pair<char, shared_ptr<WindowStrategy>>('3', make_shared<CircularWindowStrategy>()));
    auto w = windowStrategies.at('1');

    do {
        // Let the chosen demonstration object perform one (1) cycle of its work on the given source,
        // using the given strategy for window placement. The window strategy needs the number of
        // windows and their sizes to calculate the right distribution of windows on the display.
        w->reset(d->getNumberOfWindows(), s->getImage().size());
        d->show();
        d->demonstrate(*s, *w);

        // Wait for a key. In manual mode we will wait forever. In run mode we will wait for 40 msec
        // maximum, thus generating an update rate of approximately 25 fps. This loop will end if <ESC>
        // was pressed.
        key = cv::waitKey(run ? WAIT_TIME_25_FPS : WAIT_TIME_INFINITE);

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
