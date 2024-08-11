#pragma once

#include<openssl/evp.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<charconv>
#include<iostream>
#include<string>
#include<string_view>
#include<vector>

static std::string s_vals;

void md5_init()
{
    if (!s_vals.empty())
        return;
    s_vals.clear();
    char buff[5];
    for (int i = 0; i < 256; i++)
    {
        auto [ptr, ec2] = std::to_chars(buff, buff + 5, i, 16);
        if (ptr - buff == 1)
            s_vals.push_back('0');
        s_vals.append(buff, ptr - buff);
    }
}

void md5_sum(std::string_view src, std::string& dest)
{
    md5_init();
    auto *md_type = EVP_md5();
    int md_len = EVP_MD_size(md_type);
    unsigned char tmp[20];

    EVP_MD_CTX *ctx = EVP_MD_CTX_create();

// wonder if this ctx* can be reused between calculations, maybe just needs re-initializied
    EVP_MD_CTX_init(ctx);
    EVP_DigestInit_ex(ctx, md_type, NULL);
    EVP_DigestUpdate(ctx, (unsigned char*)src.data(), src.length());
    EVP_DigestFinal_ex(ctx, tmp, NULL);

    //EVP_MD_CTX_cleanup(ctx);
    EVP_MD_CTX_destroy(ctx);
    char buff[5];

    dest.clear();
    dest.reserve(md_len * 2);

    // could speed up this for loop with an array of strings built during the first call

    for (uint32_t i = 0; i < md_len; i++)
    {
        dest.append(s_vals.data() + (tmp[i] * 2), 2);
    }
}
