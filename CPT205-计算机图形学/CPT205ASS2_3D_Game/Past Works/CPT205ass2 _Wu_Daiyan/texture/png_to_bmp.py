import os
import ffmpeg

def convert_png_to_bmp(input_folder, output_folder):
    # 确保输出文件夹存在
    os.makedirs(output_folder, exist_ok=True)

    # 遍历输入文件夹中的所有文件
    for file_name in os.listdir(input_folder):
        if file_name.endswith('.png'):
            input_path = os.path.join(input_folder, file_name)
            output_path = os.path.join(output_folder, os.path.splitext(file_name)[0] + '.bmp')
            
            try:
                # 使用ffmpeg进行格式转换
                ffmpeg.input(input_path).output(output_path).run(overwrite_output=True)
                #ffmpeg.input(input_path).output(output_path, format='bmp', pix_fmt='bgra').run(overwrite_output=True)
                #ffmpeg.input(input_path).output(output_path, vcodec='bmp', pix_fmt='bgra').run(overwrite_output=True)

                print(f"转换成功: {input_path} -> {output_path}")
            except ffmpeg.Error as e:
                print(f"转换失败: {input_path}\n错误信息: {e}")

# 指定输入和输出文件夹路径
input_folder = "png"
output_folder = "bmp"

convert_png_to_bmp(input_folder, output_folder)
