package derek.xplay;

import android.annotation.SuppressLint;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.View;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


@SuppressLint("NewApi")
public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback,GLSurfaceView.Renderer,View.OnClickListener {

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);

        setRenderer(this);
        setOnClickListener(this);
    }


    public void surfaceCreated(SurfaceHolder holder) {
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


    @Override
    public void onClick(View view) {
        PlayOrPause();
    }
    public native void PlayOrPause();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }
}
