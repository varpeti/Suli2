package ml.varpeti.hf02

import android.content.Context
import android.support.v4.content.AsyncTaskLoader
import java.util.concurrent.atomic.AtomicInteger

abstract class UUIDAsyncTaskLoader<T>(context: Context) : AsyncTaskLoader<T>(context)
{
    var result: T? = null
        private set
    var hasResult = false

    init
    {
        onContentChanged()
    }

    override fun onStartLoading()
    {
        if (takeContentChanged()) forceLoad()
    }

    override fun deliverResult(data: T?)
    {
        result = data
        hasResult = true
        super.deliverResult(data)
    }

    override fun onReset()
    {
        super.onReset()
        onStopLoading()
        if (hasResult)
        {
            //onReleaseResources(result)
            result = null
            hasResult = false
        }
    }

    companion object
    {
        private val sCurrentUniqueId = AtomicInteger(0)

        val newUniqueLoaderId: Int
            get() = sCurrentUniqueId.getAndIncrement()
    }
}