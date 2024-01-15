package com;

import sun.misc.Unsafe;

import java.lang.reflect.AccessibleObject;
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.BitSet;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * 调试工具
 * T.d(obj) 输出若干对象
 * T.addr(obj) 获取对象地址
 * T.d(addr, n) 输出从[addr, addr+n]的字节值
 * T.layout(obj) 输出对象内存布局
 * T.json(obj) 对象转json
 * T.array(src, n) 从src数组拷贝n个元素组成新数组
 * T.prime(n) 构造不超过n的素数表
 */
public class T {
    public static String SPLIT = ", ";

    @SafeVarargs
    public static <Any> void d(Any... args) {
        if (null == args) {
            System.out.println("null");
            return;
        }
        if (args.length == 1) {
            System.out.println(json(args));
            return;
        }
        System.out.print(json(args[0]));
        for (int i = 1; i < args.length; i++) {
            System.out.print(SPLIT);
            System.out.print(json(args[i]));
        }
        System.out.println();
    }

    /**
     * dump内存中若干Byte值
     */
    public static void d(long addr, int bytes) {
        for (long i = 0; i < bytes; i++) {
            System.out.print(Byte.toUnsignedInt(sUnsafe.getByte(addr + i)));
        }
        System.out.println();
    }

    /**
     * 获取对象内存地址
     */
    public static void addr(Object o) {
        Object[] array = new Object[]{o};
        long baseOffset = sUnsafe.arrayBaseOffset(Object[].class);
        int addressSize = sUnsafe.addressSize();
        long objAddr = -1;
        switch (addressSize) {
            case 4:
                objAddr = sUnsafe.getInt(array, baseOffset);
                break;
            case 8:
                objAddr = sUnsafe.getLong(array, baseOffset);
                break;
            default:
                System.out.println("unsupported address size: " + addressSize);

        }
        System.out.println("0x" + Long.toHexString(objAddr));
    }

    /**
     * dump 对象内存结构
     */
    public static void layout(Object obj) {
        Object output;
        try {
            if (obj instanceof Class<?> && null != mParseClz) {
                output = mToPrintable.invoke(mParseClz.invoke(null, obj));
            } else {
                output = mToPrintable.invoke(mParseObj.invoke(null, obj));
            }
        } catch (Exception e) {
            e.printStackTrace();
            output = "Cannot find ClassLayout(maybe need deps 'org.openjdk.jol:jol-core:+').";
        }
        System.out.println(output);
    }


    /**
     * 转JSON串
     */
    public static String json(Object obj) {
        if (obj == null) {
            return "null";
        }
        Class<?> c = obj.getClass();
        // obj 是基本数据类型:Number,Boolean,String
        if (obj instanceof Number || obj instanceof Boolean || obj instanceof CharSequence) {
            if (obj instanceof CharSequence) {
                return "\"" + obj + "\"";
            }
            return String.valueOf(obj);
        }
        // obj 是数组
        if (c.isArray()) {
            StringBuilder s = new StringBuilder("[");
            for (int i = 0; i < Array.getLength(obj); i++) {
                if (i > 0) {
                    s.append(", ");
                }
                Object o = Array.get(obj, i);
                if (c.getComponentType().isPrimitive())
                    s.append(o);        //c是基本类型数组,填充obj[i]
                else s.append(json(o));
            }
            return s + "]";
        }
        // 集合也转数组
        if (obj instanceof Collection<?>) {
            return T.json(((Collection<?>) obj).toArray());
        }

        StringBuilder ans = new StringBuilder("{");
        // Map直接取键值对
        if (obj instanceof Map<?, ?>) {
            Set<? extends Map.Entry<?, ?>> set = ((Map<?, ?>) obj).entrySet();
            Iterator<?> it = set.iterator();
            Map.Entry<?, ?> entry;
            while (it.hasNext()) {
                entry = (Map.Entry<?, ?>) it.next();
                ans.append("\"").append(entry.getKey()).append("\"").append(":")
                        .append(T.json(entry.getValue())).append(it.hasNext() ? ", " : "");
            }
        } else { // obj普通对象反射取所有字段
            do {
                Field[] fields = c.getDeclaredFields();
                //对象数组权限快捷设置
                AccessibleObject.setAccessible(fields, true);
                for (Field e : fields) {
                    //加载非静态
                    if (!Modifier.isStatic(e.getModifiers())) {
                        if (!ans.toString().endsWith("{")) ans.append(", ");
                        ans.append("\"").append(e.getName()).append("\"").append(":");
                        // 取类型
                        Class<?> et = e.getType();
                        // 取值
                        Object val = null;
                        try {
                            val = e.get(obj);
                        } catch (IllegalAccessException ignore) {
                        }
                        if (et.isPrimitive()) {// 基本类型直接添加
                            ans.append(val);
                        } else {
                            ans.append(json(val));
                        }
                    }
                }
                c = c.getSuperclass();
            } while (c != null);
        }
        ans.append("}");
        return ans.toString();
    }

    /**
     * 构建数组，从src浅克隆
     */
    public static <Any> Any[] array(Any[] src, int length) {
        //获取数组类型对象
        Class<?> c = src.getClass();
        // 元素类型class
        Class<?> componentType = c.getComponentType();
        // 数组长度
        int arrayLength = Array.getLength(src);
        // 用java.reflect.Array+ 数组元素类型 和 数组长度构造数组
        Any[] newArray = (Any[]) Array.newInstance(componentType, length);
        // 把a从0开始copy到newArray
        System.arraycopy(src, 0, newArray, 0, Math.min(length, arrayLength));
        return newArray;
    }

    /**
     * 构造素数
     */
    public static List<Integer> prime(int max) {
        long start = System.nanoTime();

        List<Integer> res = new ArrayList<>((int) (max / Math.log(max) * 1.5));
        BitSet set = new BitSet(max + 1);
        int i = 2;

        while (i <= max) {
            if (!set.get(i)) {
                res.add(i);
            }
            for (int j = 0; j < res.size() && i * res.get(j) <= max; j++) {
                // 当前数和已找到的素数的积非质
                set.set(i * res.get(j));
                // 若当前数非素(a*x),那么不必再继续筛a*x * b,因为其另一个因子a*x会在i==b的时候筛掉abx
                if (i % res.get(j) == 0) {
                    break;
                }
            }
            i++;
        }
        long end = System.nanoTime();
        T.d("use: " + ((end - start) / 1_000_000_000.0));
        return res;
    }

    private static Unsafe sUnsafe;
    private static Method mParseClz;
    private static Method mParseObj;
    private static Method mToPrintable;

    static {
        try {
            Field field = Unsafe.class.getDeclaredField("theUnsafe");
            field.setAccessible(true);
            sUnsafe = (Unsafe) field.get(null);
            Class<?> clz = Class.forName("org.openjdk.jol.info.ClassLayout");
            mParseClz = clz.getDeclaredMethod("parseClass", Class.class);
            mParseObj = clz.getDeclaredMethod("parseInstance", Object.class);
            mToPrintable = clz.getDeclaredMethod("toPrintable");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
