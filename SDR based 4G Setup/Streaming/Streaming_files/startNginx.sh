sudo cp -r /home/aruna/Music/Streaming/full_video_chunks/hls /tmp
sudo /usr/local/nginx/sbin/nginx -t
sudo fuser -k 80/tcp
sudo fuser -k 8080/tcp
sudo /usr/local/nginx/sbin/nginx
