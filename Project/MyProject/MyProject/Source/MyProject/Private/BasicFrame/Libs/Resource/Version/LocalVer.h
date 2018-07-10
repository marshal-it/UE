﻿#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 本地版本系统
 */
class LocalVer : public FileVerBase
{
    public MDictionary<string, FileVerInfo> mPath2Ver_R_Dic;    // Resources 文件夹版本
    public MDictionary<string, FileVerInfo> mPath2Ver_S_Dic;    // StreamingAssets 文件夹版本
    public MDictionary<string, FileVerInfo> mPath2Ver_P_Dic;    // Persistent 文件夹版本

    public MDictionary<string, FileVerInfo> mABPath2Ver_R_Dic;    // Resources 文件夹版本
    public MDictionary<string, FileVerInfo> mABPath2Ver_S_Dic;    // StreamingAssets 文件夹版本
    public MDictionary<string, FileVerInfo> mABPath2Ver_P_Dic;    // Persistent 文件夹版本

    public string mInstallMajorVersion;    // 安装时主版本
    public string mInstallMinorVersion;    // 安装时次版本
    public string mInstallPatchVersion;    // 安装时补丁版本

    protected MDataStream mMiniDataStream;      // Mini 版本
    protected MDataStream mRDataStream;         // Resources 版本
    protected MDataStream mSDataStream;         // StreamingAssets 版本
    protected MDataStream mPDataStream;         // Persistent 版本

    protected bool mIsMiniLoaded;       // Mini 
    protected bool mIsVerSLoaded;       // Version_S
    protected bool mIsVerPLoaded;       // Version_P

    public LocalVer()
    {
        // 本地必然加载成功，因为只有打包的时候才会有 VerFileName 这些文件，不打包的时候是没有 VerFileName 这些配置文件的，因此统一处理成必然加载成功
        this.mIsMiniLoadSuccess = true;
        this.mIsVerLoadSuccess = true;

        this.mPath2Ver_R_Dic = new MDictionary<string, FileVerInfo>();
        this.mPath2Ver_S_Dic = new MDictionary<string, FileVerInfo>();
        this.mPath2Ver_P_Dic = new MDictionary<string, FileVerInfo>();

        this.mABPath2Ver_R_Dic = new MDictionary<string, FileVerInfo>();
        this.mABPath2Ver_S_Dic = new MDictionary<string, FileVerInfo>();
        this.mABPath2Ver_P_Dic = new MDictionary<string, FileVerInfo>();

        this.mIsMiniLoaded = false;
        this.mIsVerSLoaded = false;
        this.mIsVerPLoaded = false;
    }

    public void loadAllLocalVer()
    {
        this.loadMiniVerFile();
        //this.loadLocalRVer();
        this.loadLocalSVer();
        this.loadLocalPVer();
    }

    public string getInstallVersionString()
    {
        string ret = "";

        ret = string.Format("{0}-{1}-{2}", this.mInstallMajorVersion, this.mInstallMinorVersion, this.mInstallPatchVersion);

        return ret;
    }

    public void loadMiniVerFile()
    {
        //if (MacroDef.ENABLE_LOG)
        //{
        //    Ctx.msInstance.mLogSys.log("LocalVer::loadMiniVerFile, Persistent", LogTypeId.eLogAutoUpdate);
        //}

        //// 先从 PersistentPath 目录下读取,各个平台都可以同步读取
        //this.mMiniDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamPersistentDataPath, VerFileName.VER_MINI), this.onPersistentMiniLoadEventHandle);
        //this.mMiniDataStream.open();

        //// 如果读取没有成功，就从 StreamingAssetsPath (不再从 Resources) 目录下读取， StreamingAssetsPath android 下读取非 AssetBundles 需要异步
        //if (this.mFileVerInfo.isNoVerInfo())
        //{
        //    if (MacroDef.ENABLE_LOG)
        //    {
        //        Ctx.msInstance.mLogSys.log("LocalVer::loadMiniVerFile, StreamingAssets", LogTypeId.eLogAutoUpdate);
        //    }

        //    this.mIsMiniLoaded = false;     // 重新设置成 false ，防止后面的因为异步加载完成后，再调用一次的时候，会调用外面两次

        //    //this.mMiniDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamResourcesPath, "Constant", VerFileName.VER_MINI), this.onMiniLoadEventHandle);
        //    this.mMiniDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamStreamingAssetsPath, VerFileName.VER_MINI), this.onStreamingMiniLoadEventHandle);
        //    this.mMiniDataStream.open();
        //}

        ////this.mMiniLoadedDispatch.dispatchEvent(null);

        this.loadStreamingAssetsMiniVerFile();
    }

    public void loadStreamingAssetsMiniVerFile()
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("LocalVer::loadStreamingAssetsMiniVerFile, StreamingAssets", LogTypeId.eLogAutoUpdate);
        }

        this.mIsMiniLoaded = false;     // 重新设置成 false ，防止后面的因为异步加载完成后，再调用一次的时候，会调用外面两次

        //this.mMiniDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamResourcesPath, "Constant", VerFileName.VER_MINI), this.onMiniLoadEventHandle);
        this.mMiniDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamStreamingAssetsPath, VerFileName.VER_MINI), this.onStreamingMiniLoadEventHandle);
        this.mMiniDataStream.open();
    }

    public void loadPersistentMiniVerFile()
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("LocalVer::loadPersistentMiniVerFile, Persistent", LogTypeId.eLogAutoUpdate);
        }

        // 先从 PersistentPath 目录下读取,各个平台都可以同步读取
        this.mMiniDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamPersistentDataPath, VerFileName.VER_MINI), this.onPersistentMiniLoadEventHandle);
        this.mMiniDataStream.open();
    }

    protected void onStreamingMiniLoadEventHandle(IDispatchObject dispObj, uint uniqueId)
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("LocalVer::onStreamingMiniLoadEventHandle", LogTypeId.eLogAutoUpdate);
        }

        this.onMiniLoadEventHandle(dispObj, 0);

        this.mInstallMajorVersion = this.mMajorVersion;
        this.mInstallMinorVersion = this.mMinorVersion;
        this.mInstallPatchVersion = this.mPatchVersion;

        // 检查清理本地更新保存的文件
        Ctx.msInstance.mAutoClearSys.checkAutoClear();

        this.loadPersistentMiniVerFile();
    }

    protected void onPersistentMiniLoadEventHandle(IDispatchObject dispObj, uint uniqueId)
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("LocalVer::onPersistentMiniLoadEventHandle", LogTypeId.eLogAutoUpdate);
        }

        this.onMiniLoadEventHandle(dispObj, 0);

        // 设置本地加载完成标志
        this.mIsMiniLoaded = true;
        this.onAllVerLoaded();
    }

    protected void onMiniLoadEventHandle(IDispatchObject dispObj, uint uniqueId)
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("LocalVer::onMiniLoadEventHandle", LogTypeId.eLogAutoUpdate);
        }

        this.mMiniDataStream = dispObj as MDataStream;

        if (this.mMiniDataStream.isValid())
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("LocalVer::onMiniLoadEventHandle, success", LogTypeId.eLogAutoUpdate);
            }

            this.parseMiniFile(this.mMiniDataStream.readText());
        }

        this.mMiniDataStream.dispose();
        this.mMiniDataStream = null;

        //this.mMiniLoadedDispatch.dispatchEvent(null);

        //this.mIsMiniLoaded = true;
        //this.onAllVerLoaded();
    }

    // 加载 Resources 文件夹下文件对应的版本系统，目前没有了
    public void loadLocalRVer()
    {
        this.mRDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamResourcesPath, "Constant", VerFileName.VER_R), onRVerLoaded);
        this.mRDataStream.open();
    }

    public void onRVerLoaded(IDispatchObject dispObj, uint uniqueId)
    {
        this.mRDataStream = dispObj as MDataStream;

        if (this.mRDataStream.isValid())
        {
            this.loadFormText(this.mRDataStream.readText(), this.mPath2Ver_R_Dic, this.mABPath2Ver_R_Dic);
        }

        this.mRDataStream.dispose();
        this.mRDataStream = null;

        this.onAllVerLoaded();
    }

    // Android 下 StreamingAssets 目录访问只能是异步的，因此需要等待这个访问完成才行
    public void loadLocalSVer()
    {
        string path = UtilFileIO.combine(MFileSys.msDataStreamStreamingAssetsPath, VerFileName.VER_S);

        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log(string.Format("LocalVer::loadLocalSVer, path = {0}", path), LogTypeId.eLogAutoUpdate);
        }

        // 不要从 StreamingAssets 这个目录下加载 VerFileName.VER_S ，因为在 Android 上是异步加载的，因此直接放在 Resources 目录下，但是现在是不再向 Resources 目录下，本地都放在 StreamingAssets 目录

        this.mSDataStream = new MDataStream(path, this.onSVerLoaded);
        //this.mSDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamResourcesPath, "Constant", VerFileName.VER_S), this.onSVerLoaded);
        this.mSDataStream.open();
    }

    public void onSVerLoaded(IDispatchObject dispObj, uint uniqueId)
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("LocalVer::onSVerLoaded", LogTypeId.eLogAutoUpdate);
        }

        this.mSDataStream = dispObj as MDataStream;

        if (this.mSDataStream.isValid())
        {
            string text = this.mSDataStream.readText();

            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log(string.Format("LocalVer::onSVerLoaded, success, text = {0}", text), LogTypeId.eLogAutoUpdate);
            }

            //this.mSDataStream.seek(0, MSeekOrigin.eBegin);
            this.loadFormText(text, this.mPath2Ver_S_Dic, this.mABPath2Ver_S_Dic);
        }

        this.mSDataStream.dispose();
        this.mSDataStream = null;

        this.mIsVerSLoaded = true;
        this.onAllVerLoaded();
    }

    public void loadLocalPVer()
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("LocalVer::loadLocalPVer", LogTypeId.eLogAutoUpdate);
        }

        this.mPDataStream = new MDataStream(UtilFileIO.combine(MFileSys.msDataStreamPersistentDataPath, VerFileName.VER_P), this.onPVerLoaded);
        this.mPDataStream.open();
    }

    public void onPVerLoaded(IDispatchObject dispObj, uint uniqueId)
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("LocalVer::onPVerLoaded", LogTypeId.eLogAutoUpdate);
        }

        this.mPDataStream = dispObj as MDataStream;

        if (this.mPDataStream.isValid())
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("LocalVer::onPVerLoaded, success", LogTypeId.eLogAutoUpdate);
            }

            this.loadFormText(this.mPDataStream.readText(), this.mPath2Ver_P_Dic, this.mABPath2Ver_P_Dic);
        }

        this.mPDataStream.dispose();
        this.mPDataStream = null;

        this.mIsVerPLoaded = true;
        this.onAllVerLoaded();
    }

    protected void onAllVerLoaded()
    {
        if (this.mIsMiniLoaded && this.mIsVerSLoaded && this.mIsVerPLoaded)
        {
            this.mLoadedDispatch.dispatchEvent(null);
            Ctx.msInstance.setIsLocalVerLoaded(true);
        }
    }

    public int getFileVerInfo(string origPath, ref FileVerInfo fileVerInfo, bool isABAsset)
    {
        // 在 Resources 中资源是大写，在 AssetBundles 中包含的资源名字是小写，但是 StreamingAssets 或者 Persistent 中不是 AssetBundles 形式的资源，仍然是大写
        string lowerOrigPath = origPath.ToLower();
        string md5 = "";
        ResLoadType resLoadType = ResLoadType.eLoadResource;

        if (!isABAsset)
        {
            resLoadType = ResLoadType.eLoadResource;

            // 这个目录只要有就记录，例如 Windows.unity3d 这种 manifest 文件就是大写的，其它的资源目录都是小写的，为了兼容，检查大写和小写
            if (this.mPath2Ver_P_Dic.containsKey(origPath))
            {
                this.analyzeHash(this.mPath2Ver_P_Dic[origPath], ResLoadType.eLoadLocalPersistentData, ref fileVerInfo, ref md5, ref resLoadType);
            }
            else if (this.mPath2Ver_P_Dic.containsKey(lowerOrigPath))
            {
                this.analyzeHash(this.mPath2Ver_P_Dic[lowerOrigPath], ResLoadType.eLoadLocalPersistentData, ref fileVerInfo, ref md5, ref resLoadType);
            }

            if (this.mPath2Ver_S_Dic.containsKey(origPath))
            {
                // 如果两个 Hash 码是相同，就说明资源定向在 StreamAsset 目录里面
                this.analyzeHash(this.mPath2Ver_S_Dic[origPath], ResLoadType.eLoadStreamingAssets, ref fileVerInfo, ref md5, ref resLoadType);
            }
            else if (this.mPath2Ver_S_Dic.containsKey(lowerOrigPath))
            {
                this.analyzeHash(this.mPath2Ver_S_Dic[lowerOrigPath], ResLoadType.eLoadStreamingAssets, ref fileVerInfo, ref md5, ref resLoadType);
            }

            if (this.mPath2Ver_R_Dic.containsKey(origPath))
            {
                this.analyzeHash(this.mPath2Ver_R_Dic[origPath], ResLoadType.eLoadResource, ref fileVerInfo, ref md5, ref resLoadType);
            }
        }
        else
        {
            resLoadType = ResLoadType.eLoadStreamingAssets;

            // 这个目录只要有就记录
            if (this.mABPath2Ver_P_Dic.containsKey(lowerOrigPath))
            {
                this.analyzeHash(this.mABPath2Ver_P_Dic[lowerOrigPath], ResLoadType.eLoadLocalPersistentData, ref fileVerInfo, ref md5, ref resLoadType);
            }
            else if (this.mABPath2Ver_P_Dic.containsKey(origPath))
            {
                this.analyzeHash(this.mABPath2Ver_P_Dic[origPath], ResLoadType.eLoadLocalPersistentData, ref fileVerInfo, ref md5, ref resLoadType);
            }

            if (this.mABPath2Ver_S_Dic.containsKey(lowerOrigPath))
            {
                // 如果两个 Hash 码是相同，就说明资源定向在 StreamAsset 目录里面
                this.analyzeHash(this.mABPath2Ver_S_Dic[lowerOrigPath], ResLoadType.eLoadStreamingAssets, ref fileVerInfo, ref md5, ref resLoadType);
            }
            else if (this.mABPath2Ver_S_Dic.containsKey(origPath))
            {
                this.analyzeHash(this.mABPath2Ver_S_Dic[origPath], ResLoadType.eLoadStreamingAssets, ref fileVerInfo, ref md5, ref resLoadType);
            }
        }

        return (int)resLoadType;
    }

    // 比较 Hash 码
    protected void analyzeHash(
        FileVerInfo srcFileVerInfo, 
        ResLoadType defaultResLoadType, 
        ref FileVerInfo fileVerInfo, 
        ref string md5, 
        ref ResLoadType resLoadType
        )
    {
        // else 就是不修改 fileVerInfo 信息
        if (md5 == srcFileVerInfo.mFileMd5)     // 如果有 md5 ，并且 md5 == srcFileVerInfo.mFileMd5 ，就返回 srcFileVerInfo
        {
            fileVerInfo = srcFileVerInfo;
            resLoadType = defaultResLoadType;
        }
        else if (string.IsNullOrEmpty(md5))     // 如果没有 md5 ，就返回 srcFileVerInfo
        {
            fileVerInfo = srcFileVerInfo;
            md5 = fileVerInfo.mFileMd5;
            resLoadType = defaultResLoadType;
        }
    }
};

MY_END_NAMESPACE