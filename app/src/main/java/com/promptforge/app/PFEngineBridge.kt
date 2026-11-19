import android.util.Log

object PFEngineBridge {
    private const val TAG = "PFEngineBridge"

    init {
        try {
            System.loadLibrary("pfengine")
            Log.d(TAG, "引擎加载成功")
        } catch (e: Exception) {
            Log.e(TAG, "引擎加载失败：${e.message}", e)
        }
    }

    external fun initEngine(): Int
    external fun generateImage(prompt: String): ByteArray?
    external fun releaseEngine()
}
