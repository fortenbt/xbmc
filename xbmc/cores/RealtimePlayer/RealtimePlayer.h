/*
 *      Copyright (C) 2012-2015 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "cores/AudioEngine/Utils/AEChannelData.h"
#include "cores/IPlayer.h"
#include "FileItem.h"

#include "libavutil/pixfmt.h"

#include <string>

class CRealtimePlayerAudio;
class CRealtimePlayerVideo;

class CRealtimePlayer : public IPlayer
{
public:
  CRealtimePlayer(IPlayerCallback& callback);
  virtual ~CRealtimePlayer();

  // implementation of IPlayer
  virtual bool OpenFile(const CFileItem& file, const CPlayerOptions& options) override;
  virtual bool CloseFile(bool reopen = false) override;
  virtual bool IsPlaying() const override;
  virtual bool CanPause() override { return false; }
  virtual void Pause() override { }
  virtual bool IsPaused() const override { return false; }
  virtual bool HasVideo() const override { return m_video != nullptr; }
  virtual bool HasAudio() const override { return m_audio != nullptr; }
  virtual bool CanSeek() override { return false; }
  virtual void Seek(bool bPlus = true, bool bLargeStep = false, bool bChapterOverride = false) override { }
  virtual void GetAudioInfo(std::string& strAudioInfo) override { strAudioInfo = "RealtimePlayer:GetAudioInfo"; }
  virtual void GetVideoInfo(std::string& strVideoInfo) override { strVideoInfo = "RealtimePlayer:GetVideoInfo"; }
  virtual void GetGeneralInfo(std::string& strGeneralInfo) override { strGeneralInfo = "RealtimePlayer:GetGeneralInfo"; }

  // Game API
  void VideoFrame(const uint8_t* data, unsigned int size, unsigned int width, unsigned int height, AVPixelFormat format);
  void AudioFrames(const uint8_t* data, unsigned int size, unsigned int frames, AEDataFormat format);

protected:
  CRealtimePlayerVideo* const m_video;
  CRealtimePlayerAudio* const m_audio;
  CFileItemPtr                m_file;
  CPlayerOptions              m_options;
};
