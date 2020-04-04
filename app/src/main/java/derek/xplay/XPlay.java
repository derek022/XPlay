package derek.xplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback {

    public XPlay(Context context) {
        super(context);
    }

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);

    }


    public void surfaceCreated(SurfaceHolder holder)
    {
//        super.surfaceCreated(holder);
        // 初始化 opengl 显示
        InitView(holder.getSurface());
    }

    private native void InitView(Surface holder);

    public void surfaceChanged(SurfaceHolder holder, int format, int width,
                               int height)
    {
//        super.surfaceChanged(holder,format,width,height);
    }


    public void surfaceDestroyed(SurfaceHolder holder)
    {
//        super.surfaceDestroyed(holder);
    }
}
