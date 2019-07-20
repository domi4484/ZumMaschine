# Istruzioni:
# https://www.digitalocean.com/community/tutorials/how-to-set-up-nginx-server-blocks-virtual-hosts-on-ubuntu-14-04-lts

server {

#    listen      138.68.87.82:80 default;
    listen      138.68.87.82:80;

    server_name lowerclassclothing.com www.lowerclassclothing.com;

    access_log  /var/log/nginx/lowerclassclothing.access.log;
    error_log   /var/log/nginx/lowerclassclothing.error.log;

    # Allow bigger body size for nextcloud clients uploads
    client_max_body_size        1G;
    client_body_buffer_size     400M;

    location / {
        proxy_pass  http://127.0.0.1:8000;
        proxy_next_upstream error timeout invalid_header http_500 http_502 http_503 http_504;

        proxy_buffer_size 128k;
        proxy_buffers 16 64k;
        proxy_redirect off;

        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }

    location ~* /web/static/ {
        proxy_buffering off;
        proxy_pass http://127.0.0.1:8000;
    }

#    listen 443 ssl; # managed by Certbot
#    ssl_certificate /etc/letsencrypt/live/customcut.ch/fullchain.pem; # managed by Certbot
#    ssl_certificate_key /etc/letsencrypt/live/customcut.ch/privkey.pem; # managed by Certbot
#    include /etc/letsencrypt/options-ssl-nginx.conf; # managed by Certbot
#    ssl_dhparam /etc/letsencrypt/ssl-dhparams.pem; # managed by Certbot


}
