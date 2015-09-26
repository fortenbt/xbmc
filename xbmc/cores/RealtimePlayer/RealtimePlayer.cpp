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

#include "RealtimePlayer.h"
#include "RealtimePlayerAudio.h"
#include "RealtimePlayerVideo.h"

CRealtimePlayer::CRealtimePlayer(IPlayerCallback& callback) :
  IPlayer(callback),
  m_video(new CRealtimePlayerVideo),
  m_audio(new CRealtimePlayerAudio)
{
}

CRealtimePlayer::~CRealtimePlayer()
{
  delete m_video;
  delete m_audio;
}

bool CRealtimePlayer::OpenFile(const CFileItem& file, const CPlayerOptions& options)
{
  if (IsPlaying())
    CloseFile();

  m_file = CFileItemPtr(new CFileItem(file));
  m_options = options;
  return true;
}

bool CRealtimePlayer::CloseFile(bool reopen /* = false */)
{
  if (!IsPlaying())
    return true; // Already closed

  CFileItemPtr lastFile;
  lastFile.swap(m_file);

  if (reopen)
    return OpenFile(*lastFile, m_options);

  return true; 
}

bool CRealtimePlayer::IsPlaying() const
{
  return m_file.get() != nullptr;
}

void CRealtimePlayer::VideoFrame(const uint8_t* data, unsigned int size, unsigned int width, unsigned int height, AVPixelFormat format)\
{
  m_video->VideoFrame(data, size, width, height, format);
}

void CRealtimePlayer::AudioFrames(const uint8_t* data, unsigned int size, unsigned int frames, AEDataFormat format)
{
  m_audio->AudioFrames(data, size, frames, format);
}
