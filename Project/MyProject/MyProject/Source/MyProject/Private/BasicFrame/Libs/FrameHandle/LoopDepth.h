﻿#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class LoopDepth
{
    private int mLoopDepth;         // 是否在循环中，支持多层嵌套，就是循环中再次调用循环
    private CallFuncObjectNoParam mIncHandle;     // 增加处理器
    private CallFuncObjectNoParam mDecHandle;     // 减少处理器
    private CallFuncObjectNoParam mZeroHandle;    // 减少到 0 处理器

    public LoopDepth()
    {
        this.mLoopDepth = 0;
        this.mIncHandle = null;
        this.mDecHandle = null;
        this.mZeroHandle = null;
    }

    public void init()
    {

    }

    public void dispose()
    {
        if(null != this.mIncHandle)
        {
            this.mIncHandle.dispose();
            this.mIncHandle = null;
        }
        if(null != this.mDecHandle)
        {
            this.mDecHandle.dispose();
            this.mDecHandle = null;
        }
        if (null != this.mZeroHandle)
        {
            this.mZeroHandle.dispose();
            this.mZeroHandle = null;
        }
    }

    public void setIncHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> value, uint eventId)
    {
        if(null == this.mIncHandle)
        {
            this.mIncHandle = new CallFuncObjectNoParam();
        }

        this.mIncHandle.setThisAndHandleNoParam(pThis, value, 0);
    }

    public void setDecHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> value, uint eventId)
    {
        if (null == this.mDecHandle)
        {
            this.mDecHandle = new CallFuncObjectNoParam();
        }

        this.mDecHandle.setThisAndHandleNoParam(pThis, value, eventId);
    }

    public void setZeroHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> value, uint eventId)
    {
        if (null == this.mZeroHandle)
        {
            this.mZeroHandle = new CallFuncObjectNoParam();
        }

        this.mZeroHandle.setThisAndHandleNoParam(pThis, value, eventId);
    }

    public void _incDepth()
    {
        ++this.mLoopDepth;

        if(null != this.mIncHandle)
        {
            this.mIncHandle.call();
        }
    }

    public void _decDepth()
    {
        --this.mLoopDepth;

        if (null != this.mDecHandle)
        {
            this.mDecHandle.call();
        }

        if(0 == this.mLoopDepth)
        {
            if (null != this.mZeroHandle)
            {
                this.mZeroHandle.call();
            }
        }

        if(this.mLoopDepth < 0)
        {
            this.mLoopDepth = 0;
            // 错误，不对称
            UnityEngine.Debug.LogError("LoopDepth::_decDepth, Error !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        }
    }

    public bool _isInDepth()
    {
        return this.mLoopDepth > 0;
    }
}

MY_END_NAMESPACE