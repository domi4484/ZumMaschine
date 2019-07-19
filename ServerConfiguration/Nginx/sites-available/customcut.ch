server {
    listen      138.68.87.82:80 default;
    server_name customcut.ch www.customcut.ch;

    access_log  /var/log/nginx/customcut.access.log;
    error_log   /var/log/nginx/customcut.error.log;

    # Allow bigger body size for nextcloud clients uploads
    client_max_body_size        10G;
    client_body_buffer_size     400M;

    location /nextcloud/ {
       rewrite ^/nextcloud(.*) $1 break;
       proxy_pass http://127.0.0.1:81;
    }

    location /collabora/ {
       rewrite ^/collabora(.*) $1 break;
       proxy_pass http://127.0.0.1:9980;
    }

    location / {
        proxy_pass  http://127.0.0.1:8069;
        proxy_next_upstream error timeout invalid_header http_500 http_502 http_503 http_504;

        proxy_buffer_size 128k;
        proxy_buffers 16 64k;
        proxy_redirect off;

        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        # proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        # proxy_set_header X-Forwarded-Proto https;
    }

    location ~* /web/static/ {
        proxy_buffering off;
        proxy_pass http://127.0.0.1:8069;
    }

    listen 443 ssl; # managed by Certbot
    ssl_certificate /etc/letsencrypt/live/customcut.ch/fullchain.pem; # managed by Certbot
    ssl_certificate_key /etc/letsencrypt/live/customcut.ch/privkey.pem; # managed by Certbot
    include /etc/letsencrypt/options-ssl-nginx.conf; # managed by Certbot
    ssl_dhparam /etc/letsencrypt/ssl-dhparams.pem; # managed by Certbot


}


