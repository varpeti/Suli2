package ml.varpeti.hf06


import android.content.pm.ActivityInfo
import android.support.test.espresso.Espresso.onView
import android.support.test.espresso.action.ViewActions.click
import android.support.test.espresso.assertion.ViewAssertions.matches
import android.support.test.espresso.matcher.ViewMatchers.*
import android.support.test.filters.LargeTest
import android.support.test.rule.ActivityTestRule
import android.support.test.runner.AndroidJUnit4
import android.view.View
import android.view.ViewGroup
import org.hamcrest.Description
import org.hamcrest.Matcher
import org.hamcrest.Matchers.allOf
import org.hamcrest.TypeSafeMatcher
import org.junit.Rule
import org.junit.Test
import org.junit.runner.RunWith

@LargeTest
@RunWith(AndroidJUnit4::class)
class MainActivityTest {

    @Rule
    @JvmField
    var mActivityTestRule = ActivityTestRule(MainActivity::class.java)


    // Igen, kézzel írtam meg mert nem működik az Ecspresso recorder által generált test.

    @Test
    fun mainActivityTest()
    {
        val b0 = onView(allOf(withId(R.id.b0)))
        val b00 = onView(allOf(withId(R.id.b00)))
        val b01 = onView(allOf(withId(R.id.b01)))
        val b0bs = onView(allOf(withId(R.id.b0bs)))
        val b0del = onView(allOf(withId(R.id.b0del)))


        val b1 = onView(allOf(withId(R.id.b1)))
        val b10 = onView(allOf(withId(R.id.b10)))
        val b11 = onView(allOf(withId(R.id.b11)))
        val b1bs = onView(allOf(withId(R.id.b1bs)))
        val b1del = onView(allOf(withId(R.id.b1del)))


        val b2 = onView(allOf(withId(R.id.b2)))
        val add = onView(allOf(withId(R.id.add)))
        val sub = onView(allOf(withId(R.id.sub)))
        val popb0 = onView(allOf(withId(R.id.popb0)))
        val popb1 = onView(allOf(withId(R.id.popb1)))

        b01.perform(click())
        b0.check(matches(withText("1")))

        b00.perform(click())
        b0.check(matches(withText("10")))

        b01.perform(click())
        b0bs.perform(click())
        b0.check(matches(withText("10")))

        b11.perform(click())
        b1.check(matches(withText("1")))

        b10.perform(click())
        b1.check(matches(withText("10")))

        b1bs.perform(click())
        b11.perform(click())
        b11.perform(click())
        b1.check(matches(withText("111")))

        add.perform(click())
        b2.check(matches(withText("1001")))

        sub.perform(click())
        b2.check(matches(withText("-101")))

        popb0.perform(click())
        b0.check(matches(withText("-101")))

        b0del.perform(click())
        b0.check(matches(withText("")))

        popb1.perform(click())
        b1.check(matches(withText("-101")))

        sub.perform(click())
        b2.check(matches(withText("101")))

        b1bs.perform(click())
        b1bs.perform(click())
        b1bs.perform(click())
        b1.check(matches(withText("-")))

        add.perform(click())
        b2.check(matches(withText("0")))

        b1del.perform(click())
        b1.check(matches(withText("")))

        add.perform(click())
        b2.check(matches(withText("0")))

        for (i in 0..40) b11.perform(click())
        b1.check(matches(withText("1111111111111111111111111111111")))

        b01.perform(click())
        add.perform(click())
        b2.check(matches(withText("-10000000000000000000000000000000")))

        mActivityTestRule.activity.requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        Thread.sleep(1000)

        b0.check(matches(withText("1")))
        b1.check(matches(withText("1111111111111111111111111111111")))
        b2.check(matches(withText("-10000000000000000000000000000000")))

        mActivityTestRule.activity.requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT
        Thread.sleep(1000)

        b0.check(matches(withText("1")))
        b1.check(matches(withText("1111111111111111111111111111111")))
        b2.check(matches(withText("-10000000000000000000000000000000")))
    }

    private fun childAtPosition(
        parentMatcher: Matcher<View>, position: Int
    ): Matcher<View> {

        return object : TypeSafeMatcher<View>() {
            override fun describeTo(description: Description) {
                description.appendText("Child at position $position in parent ")
                parentMatcher.describeTo(description)
            }

            public override fun matchesSafely(view: View): Boolean {
                val parent = view.parent
                return parent is ViewGroup && parentMatcher.matches(parent)
                        && view == parent.getChildAt(position)
            }
        }
    }
}
